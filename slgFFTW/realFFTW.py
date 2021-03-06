# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.2
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_realFFTW', [dirname(__file__)])
        except ImportError:
            import _realFFTW
            return _realFFTW
        if fp is not None:
            try:
                _mod = imp.load_module('_realFFTW', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _realFFTW = swig_import_helper()
    del swig_import_helper
else:
    import _realFFTW
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


class realFFTW(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, realFFTW, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, realFFTW, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _realFFTW.new_realFFTW(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _realFFTW.delete_realFFTW
    __del__ = lambda self : None;
    def setInput(self, *args): return _realFFTW.realFFTW_setInput(self, *args)
    def getMagnitude(self, *args): return _realFFTW.realFFTW_getMagnitude(self, *args)
    def getPhase(self, *args): return _realFFTW.realFFTW_getPhase(self, *args)
    def setFFTCoef(self, *args): return _realFFTW.realFFTW_setFFTCoef(self, *args)
    def getInversed(self, *args): return _realFFTW.realFFTW_getInversed(self, *args)
    def cpyOutput(self, *args): return _realFFTW.realFFTW_cpyOutput(self, *args)
    def setIn(self, *args): return _realFFTW.realFFTW_setIn(self, *args)
    def getIn(self, *args): return _realFFTW.realFFTW_getIn(self, *args)
    def createPlan(self): return _realFFTW.realFFTW_createPlan(self)
    def destroyPlan(self): return _realFFTW.realFFTW_destroyPlan(self)
    def forwardTransform(self): return _realFFTW.realFFTW_forwardTransform(self)
    def inverseTransform(self): return _realFFTW.realFFTW_inverseTransform(self)
    def getOut(self, *args): return _realFFTW.realFFTW_getOut(self, *args)
realFFTW_swigregister = _realFFTW.realFFTW_swigregister
realFFTW_swigregister(realFFTW)

# This file is compatible with both classic and new-style classes.


