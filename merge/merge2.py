import re
import os,sys

if os.path.exists("/build/ltesdkroot"):
    import site
    site.addsitedir("/build/ltesdkroot/Tools/Tools/python/python-2.7.2/lib/python2.7/site-packages/Jinja2-2.6-py2.7.egg/")
    site.addsitedir("/build/ltesdkroot/Tools/Tools/python/python-2.7.2/lib/python2.7/site-packages/lxml-2.3.3-py2.7-linux-x86_64.egg/")

from lxml import etree

class Distname:
    def __init__(self,dn):
        if len(dn)==0:
            raise Exception("Invalid object")
        self.dn = dn
        result = re.search("(.*/)*([A-Z_]*)-([0-9]*)",self.dn)
        if len(result.group(1))==0:
            self.parentDN = ""
        else:
            self.parentDN = result.group(1)[:-1]
        self.className = result.group(2)
        self.id = result.group(3)

    def hasParent(self):
        if self.parentDN == "":
            return False
        return True
 
    def getParent(self):
        if self.parentDN == "":
            raise Exception("No parent")
        return Distname(self.parentDN)

class ManagedObject:
    @staticmethod
    def isMo(ob):
        return ob.tag == 'managedObject'
    
    def __init__(self,ob):
        if not ManagedObject.isMo(ob):
            raise Exception('Object is not MO')
        self.object = ob
        self.distNameOb = Distname(self.object.attrib.get('distName'))
        self.distName = self.distNameOb.dn
        self.className = self.distNameOb.className
        self.id = self.distNameOb.id
        if self.object.attrib.get('class') != self.className:
            print("%s has wrong class"%distName)
            raise Exception('MO has wrong DN or class name')

    def getDistname(self):
        return self.distNameOb

    def hasParamWithName(self,name):
        for p in self.object.iterchildren():
            if p.attrib.get('name') == name:
                return True
        return False
class MoBuilder:
    def __init__(self,defaults):
        self.defaults = defaults
    def create(self, dn, vals=None):
        return ManagedObject(self.defaults[0])
     
class IMDump:
    def __init__(self,defaults,template):
        self.defaultMOs = []
        self.parsed_template = etree.parse(template)
        self.parsed_defaults = etree.parse(defaults)
        self.defaults_root = self.parsed_defaults.getroot()
        self.template_root = self.parsed_template.getroot()
        self.mos = []
        self.parseDefaults()
        self.parseTemplate()

    def parseDefaults(self):
        for ob in self.defaults_root.iterchildren():
            try:
                #print(ob.attrib.get('class'))
                mo = ManagedObject(ob)
                self.defaultMOs.append(mo)
                #print(len(self.defaultMOs))
            except Exception as ex:
                print(ex.args)
                continue
        print("Available default MO's:")
        print(len(self.defaultMOs))
        for ob in self.defaultMOs:
            print(ob.className)
        self.builder = MoBuilder(self.defaultMOs)

    def parseTemplate(self):
        for ob in self.template_root.iterchildren():
            try:
                mo = ManagedObject(ob)
                self.mos.append(mo)
            except Exception:
                continue
    def findDN(self,dn):
        for mo in self.mos:
            if mo.distName == dn:
                return mo
        raise Exception("Distname not found",dn)

    def addMO(self, mo):
        self.mos.append(mo)
        self.template_root.append(mo.object);
    def fillMissingMos(self):
        missingDNs=[]
        for mo in self.mos:
            dn = mo.getDistname()
            while dn.hasParent():
                try:
                    dn = dn.getParent()
                    self.findDN(dn.parentDN)
                except Exception:
                    if(not dn.parentDN in missingDNs):
                        print("Adding: %s"%dn.parentDN)
                        missingDNs.append(dn.parentDN)
        for dn in missingDNs:
            print(dn)
            self.addMO(self.builder.create(dn))
    def merge(self):
        self.fillMissingMos()



if __name__ == "__main__":
    defa = sys.argv[1]
    tmpl = sys.argv[2]
    result = sys.argv[3]
    print("Starting..")
    dump = IMDump(defa,tmpl)
    dump.merge()


#addDefaultMo(parsed_template.getroot(),""
#print(defaults)
#print(findDefault(getType("/MRBTS-1/RAT-1/LNBTS-1/BTS_CONF-1/NP-1/MRBTS_A-1/LNBTS_A-1/LNCEL_A-1")[1]))

#new.append(findDefault(getType("/MRBTS-1/RAT-1/LNBTS-1/BTS_CONF-1/NP-1/MRBTS_A-1/LNBTS_A-1/LNCEL_A-1")[1]))

