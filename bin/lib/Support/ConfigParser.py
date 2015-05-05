import re

class ConfigParser:
    """Class to read configuration files.

    The file may contain # comments.

    Every single non-empty non-comment line defines a config variable in the
    follow way:
    
    variable_name = [type:]variable_value

    where the "type:" is optional. If not specified it is considered a string.
    The types could be int, complex, bool, float. In case we need to specify 
    a list, we do it in this way:

    variable_name = list:[type:]value, [type:]value, ...
    """

    def __init__(self, fname):
        """Constructor taking the file path to a configuration txt file
        """
        self.fname = fname
        self.data = self.__parse_config_file()

    def __parse_vals(self, text):
        if text:
            if re.match(r'^list:', text):
                values = self.__parse_list(text[5:])
            elif re.match(r'^bool:', text):
                values = self.__parse_bool(text[5:])
            elif re.match(r'^int:', text):
                values = self.__parse_type(text[4:], int)
            elif re.match(r'^float:', text):
                values = self.__parse_type(text[6:], float)
            elif re.match(r'^long:', text):
                values = self.__parse_type(text[5:], long)
            elif re.match(r'^complex:', text):
                values = self.__parse_type(text[8:], complex)
            else:
                values = text
        else:
            values = ""
        return values

    def __parse_list(self, text):
        values = text.split(',')
        return [__parse_vals(val.strip(), self.fname) for val in values]

    def __parse_bool(self, text):
        if text.lower() == "true":
            return True
        elif text.lower() == "false":
            return False
        else:
            raise ValueError('Could not convert value %s to bool in file %s' % \
                            (text, self.fname))

    def __parse_type(self, text, type_):
        try:
            return type_(text.strip())
        except ValueError as e:
            raise ValueError('Could not convert value %s to %s in file %s' % \
                    (text, type_.__name__, self.fname))

    def __parse_config_file(self):
        res = {}
        fd = open(self.fname, 'r')

        for line in fd.readlines():
            line = line.strip()
            if line and line.find('#') >= 0:
                line = line[:line.find('#')]
                if not line:
                    continue
            m = re.match(r"([^=]+)=(.+)",line)
            if m:
                values = self.__parse_vals(m.groups()[1].strip())
                res[m.groups()[0].strip()] = values
        fd.close()

        return res

    def get_value(self, key):
        """Returns the value for a key given in the configuration file.
        If the key does not exist, returns None
        """
        if key in self.data:
            return self.data[key]

