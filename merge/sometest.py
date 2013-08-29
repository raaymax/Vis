import copy
class Test:
    def __init__(self):
        self.test = "OK"
        print("Construction of Test")

class Test2(Test):
    def __init__(self):
        Test.__init__(self)
        print("constructor2")

t = Test2()

