import logging
from lxml import etree
from lxml import objectify


def read_xml(fname):
    result_set = ResultSet()
    try:
        tree = objectify.parse (fname)
        root = tree.getroot ()

        for datapointset in root.iter ('datapointset'):
            for criteria in datapointset.iter('criteria'):
                criteria_el = Criteria (criteria.get('granularity'),
                                        criteria.get('wrong_checker_is_fp'),
                                        criteria.get('minimum'))
                result_set.add(criteria_el)

                for datapoint in criteria.iter ('datapoint'):
                    criteria_el.add (Datapoint.from_xml (datapoint))

    except etree.XMLSyntaxError:
        logging.error('Unable to parse xml file [%s]' % fname)
        return

    return result_set


class ResultSet:
    def __init__ (self, resultset_name = None, sourcename = None, args = None):
        self.__resultset_name__ = resultset_name
        self.__source_name__ = sourcename
        self.__criteria__ = []
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

    def add (self, criteria):
        self.__criteria__.append (criteria)

    def criterias (self):
        for criteria in self.__criteria__:
            yield criteria


class Criteria:
    def __init__ (self, granularity, wrong_checker_is_fp, minimum):
        # self.__name__ = name
        self.__granularity__ = granularity
        self.__wrong_checker_is_fp__ = wrong_checker_is_fp
        self.__minimum__ = minimum
        self.__datapoint__ = []

    def getGranularity (self):
        return self.__granularity__

    def getWrongCheckerIsFp (self):
        return self.__wrong_checker_is_fp__

    def getMinimum (self):
        return self.__minimum__

    def datapoints (self):
        for datapoint in self.__datapoint__:
            yield datapoint

    def add (self, datapoint):
        self.__datapoint__.append (datapoint)


class Datapoint:
    #
    # Factory method for creating a Datapoint object from an xml document.
    #
    @staticmethod
    def from_xml (xml) :
        return Datapoint (xml.get ('directory'),
                          xml.get ('filename'),
                          int (xml.get ('line')),
                          xml.get ('function'),
                          xml.get ('info'),
                          xml.get ('package'),
                          xml.get ('classpath'),
                          xml.get ('sourcepath'))

    def __init__ (self, directory, filename, line, function="", info="", \
                    package="", classpath="", sourcepath=""):
        self.__directory__ = directory
        self.__filename__ = filename
        self.__line__ = int(line)
        # self.__compiler__ = compiler
        # self.__args__ = args
        # self.__bugs__ = []
        self.__function__ = function
        self.__info__ = info
        self.__package__ = package
        self.__classpath__ = classpath
        self.__sourcepath__ = sourcepath

    def setDirectory (self, directory):
        self.__directory__ = directory

    def getDirectory (self):
        return self.__directory__

    def getPackage (self):
        return self.__package__

    def getClasspath (self):
        return self.__classpath__

    def getSourcepath (self):
        return self.__sourcepath__

    def getFilename (self):
        return self.__filename__

    def getLine (self):
        return self.__line__

    # def setCompiler (self, compiler):
    #     self.__compiler__ = compiler

    # def getCompiler (self):
    #     return self.__compiler__

    def getFunction (self):
        return self.__function__

    def getInfo (self):
        return self.__info__

