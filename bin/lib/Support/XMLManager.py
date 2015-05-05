from lxml import etree
from lxml import objectify


def read_xml(fname):
    result_set = ResultSet()
    try:
        tree = objectify.parse (fname)
        root = tree.getroot ()

        for result in root.iter ('result'):
            if result.get ('name'):
                result_set.setName (result.get ('name'))

            if result.get ('source'):
                result_set.setSource (result.get ('source'))

            if result.get ('args'):
                result_set.setArgs (result.get ('args'))

            for weakness in result.iter('weakness'):
                weakness_el = Weakness (weakness.get('id'))
                result_set.add(weakness_el)

                for suite in weakness.iter('suite'):
                    suite_el = Suite (suite.get ('dir'), suite.get ('tool'), suite.get ('args'))
                    weakness_el.add (suite_el)

                    for bug in suite.iter ('bug'):
                        suite_el.add (Bug.from_xml (bug))

        result_set.setSource(root.get('source'))

    except etree.XMLSyntaxError:
        return

    return result_set


class ResultSet:
    def __init__ (self, resultset_name = None, sourcename = None, args = None):
        self.__resultset_name__ = resultset_name
        self.__source_name__ = sourcename
        self.__weaknesses__ = []
        self.__args__ = ''

    def setName (self, name):
        self.__resultset_name__ = name

    def getName (self):
        return self.__resultset_name__

    def setArgs (self, args):
        self.__args__ = args

    def getArgs (self):
        return self.__args__

    def setSource (self, name):
        self.__source_name__ = name

    def getSource (self):
        return self.__source_name__

    def add (self, weakness):
        self.__weaknesses__.append (weakness)

    def weaknesses (self):
        for weakness in self.__weaknesses__:
            yield weakness


class Weakness:
    def __init__ (self, name):
        self.__name__ = name
        self.__suites__ = []

    def setName (self, name):
        self.__name__ = name

    def getName (self):
        return self.__name__

    def suites (self):
        for suite in self.__suites__:
            yield suite

    def add (self, suite):
        self.__suites__.append (suite)


class Suite:
    def __init__ (self, directory, compiler, args):
        self.__directory__ = directory
        self.__compiler__ = compiler
        self.__args__ = args
        self.__bugs__ = []

    def setDirectory (self, directory):
        self.__directory__ = directory

    def getDirectory (self):
        return self.__directory__

    def setCompiler (self, compiler):
        self.__compiler__ = compiler

    def getCompiler (self):
        return self.__compiler__

    def setArgs (self, args):
        self.__args__ = args

    def getArgs (self):
        return self.__args__

    def bugs (self):
        for bug in self.__bugs__:
            yield bug

    def add (self, bug):
        self.__bugs__.append (bug)


#
# A Bug is a single result from running a build. This class is used for
# analysis purposes. Probability_info can be any string necessary for a
# \a Tool to identify the result from the Bug.
#
class Bug:
    #
    # Factory method for creating a Bug object from a \a xml document.
    #
    @staticmethod
    def from_xml (xml) :
        return Bug (xml.get ('filename'),
                    xml.get ('function'),
                    int (xml.get ('line')),
                    xml.get ('probability_info'))

    def __init__ (self, filename, function, line, probability_info):
        self.__filename__ = filename
        self.__function__ = function
        self.__line__ = line
        self.__info__ = probability_info

    def setFilename(self, filename):
        self.__filename__ = filename

    def getFilename(self):
        return self.__filename__

    def setFunction(self, function):
        self.__function__ = function

    def getFunction(self):
        return self.__function__

    def setLine(self, line):
        self.__line__ = line

    def getLine(self):
        return self.__line__

    def setInfo(self, info):
        self.__info__ = info

    def getInfo(self):
        return self.__info__

