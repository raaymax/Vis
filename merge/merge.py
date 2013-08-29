import re
import os,sys,copy

if os.path.exists("/build/ltesdkroot"):
    import site
    site.addsitedir("/build/ltesdkroot/Tools/Tools/python/python-2.7.2/lib/python2.7/site-packages/Jinja2-2.6-py2.7.egg/")
    site.addsitedir("/build/ltesdkroot/Tools/Tools/python/python-2.7.2/lib/python2.7/site-packages/lxml-2.3.3-py2.7-linux-x86_64.egg/")

from lxml import etree

class Distname:
    def __init__(self,dn):
        if dn == None:
            raise Exception("dn is None")
        if len(dn)==0:
            raise Exception("Invalid object")
        self.raw = dn
        result = re.search("(.*/)*([A-Z_]*)-([0-9]*)",self.raw)
        if len(result.group(1))==0:
            self.parentDN = ""
        else:
            self.parentDN = result.group(1)[:-1]
        self.className = result.group(2)
        self.id = result.group(3)

        self.level = -1
        for c in self.raw:
            if c == '/':
                self.level += 1


    def hasParent(self):
        if self.parentDN == "":
            return False
        return True

    def __eq__(self, other):
        return self.raw == other

    def getParent(self):
        if self.parentDN == "":
            raise Exception("No parent")
        return Distname(self.parentDN)
class ManagedObjectBase:
    @staticmethod
    def isMo(ob):
        return ob.tag == 'managedObject'
    def __init__(self,ob):
        if not ManagedObject.isMo(ob):
            raise Exception('Object is not MO: %s'%ob.tag)
        self.object = copy.deepcopy(ob)
        self.className = self.object.attrib.get('class')


class ManagedObject(ManagedObjectBase):

    def __init__(self,ob):
        ManagedObjectBase.__init__(self,ob)
        self.distName = Distname(self.object.attrib.get('distName'))
        self.childs = []
        self.parent = None
        if self.className != self.distName.className:
            raise Exception('MO has wrong DN or class name')

    def hasParent(self):
        return self.parent != None

    def getParent(self):
        return self.parent

    def addChild(self, mo):
        mo.parent = self
        self.childs.append(mo)

    def find(self, dn):
        if self.distName == dn:
            return self
        for i in self.childs:
            if i.distName == dn:
                return i

            ob = i.find(dn)
            if ob != None:
                return ob
        return None
    def execute(self, exe):
        exe.proc(self)
        for child in self.childs:
            child.execute(exe)

    def hasParamWithName(self,name):
        for p in self.object.iterchildren():
            if p.attrib.get('name') == name:
                return True
        return False
class ManagedObjectBuilder:
    def __init__(self,defaults):
        self.defaults = defaults
    def findClass(self,className):
        for d in self.defaults:
            if d.className == className:
                return d
        return None

    def create(self,dn,mo=None):
        default = self.findClass(dn.className)
        new = etree.Element("managedObject")
        if default != None:
            if mo != None:
                for p in mo.object.iterchildren():
                    new.append(copy.deepcopy(p))
            for p in default.object.iterchildren():
                name = p.attrib.get("name")
                if mo == None or not mo.hasParamWithName(name):
                    new.append(copy.deepcopy(p))
        new.set('distName',dn.raw)
        new.set('class',dn.className)
        return ManagedObject(new)
class TreeBuilder:
    def __init__(self):
        self.root = etree.Element("IMdump")
        self.tree = etree.ElementTree(self.root)
    def proc(self, mo):
        self.root.append(copy.deepcopy(mo.object))
    def get(self):
        return self.tree
class IMdump:
    def __init__(self, defaults,template):
        self.defaultMOs = []
        self.parsed_template = etree.parse(template)
        self.parsed_defaults = etree.parse(defaults)
        self.defaults_root = self.parsed_defaults.getroot()
        self.template_root = self.parsed_template.getroot()
        self.mos = []
        self.parseDefaults()
        self.parseTemplates()
        self.dumpRoot = None
        self.db = []

    def parseDefaults(self):
        for ob in self.defaults_root.iterchildren():
            try:
                mo = ManagedObjectBase(ob)
                self.defaultMOs.append(mo)
            except Exception as ex:
                continue
        self.builder = ManagedObjectBuilder(self.defaultMOs)
    def parseTemplates(self):
        for ob in self.template_root.iterchildren():
            try:
                mo = ManagedObject(ob)
                self.mos.append(mo)
            except Exception as ex:
                continue
        
        
    def createTree(self):
        self.mos = sorted(self.mos, key=lambda mo: mo.distName.level)
        self.dumpRoot = self.mos[0]
        for mo in self.mos:
            parent = None
            if not mo.distName.hasParent():
                continue

            parentDN = mo.distName.getParent()
            current = mo
            while current != None:
                if mo == current:
                    current = self.builder.create(mo.distName,mo)
                    self.db.append(current)

                parent = self.dumpRoot.find(parentDN)
                if parent != None:
                    parent.addChild(current)
                    break
                else:
                    parent = self.builder.create(parentDN)
                    self.db.append(parent)
                    parent.addChild(current)
                    current = parent
                    parent = None
             
                if current.distName.hasParent():
                    parentDN = current.distName.getParent()
                else:
                    self.dumpRoot = current
                    break

    def create(self):
        self.createTree()
        tree = TreeBuilder()
        self.dumpRoot.execute(tree)
        print(etree.tostring(tree.get()).decode("utf-8"))

if __name__ == "__main__":
    defa = sys.argv[1]
    tmpl = sys.argv[2]
    dump = IMdump(defa,tmpl)
    dump.create()


