from merge import Distname
import unittest

class Distname_tests(unittest.TestCase):
    def setUp(self):
        self.distname = "/MRBTS-2/RAT-3/LNBTS-4"
        self.dn = Distname(self.distname)


    def checkDN(self,distname,parent,className,id):
        self.assertEqual(self.dn.raw,distname)
        self.assertEqual(self.dn.id,id)
        self.assertEqual(self.dn.parentDN, parent)
        self.assertEqual(self.dn.className,className)
    def test_has_parent(self):
        self.assertEqual(self.dn.hasParent(),True)
        dn = Distname("/MRBTS-1")
        self.assertEqual(dn.hasParent(),False)
    def test_get_parent(self):
        self.checkDN(self.distname,"/MRBTS-2/RAT-3","LNBTS","4")
        self.dn = self.dn.getParent()
        self.checkDN("/MRBTS-2/RAT-3","/MRBTS-2","RAT","3")
        self.dn = self.dn.getParent()
        self.checkDN("/MRBTS-2","","MRBTS","2")
        with self.assertRaises(Exception):
            self.dn = self.dn.getParent()
    def test_invalid_creation(self):
        with self.assertRaises(Exception):
            Distname("")
    def test_level_calculation(self):
        self.assertEqual(self.dn.level,2)

if __name__ == '__main__':
    unittest.main()


