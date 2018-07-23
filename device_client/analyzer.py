import sys
import re
from collections import OrderedDict

class Header:
    hashtbale = OrderedDict()
    requestOrResponse = 0
    size = 0
    name = ""
    def __init__ (self):
        self.hashtbale = OrderedDict()
        self.size = 0
        self.name = ""

    def size (self):
        return self.size

def headerDiff(header_list):
    i = 0
    length = len(header_list)
    redundacy = 0
    total_size = 0
    for elm in header_list:
        total_size += elm.size;

    while i < length:
        j = i + 1;
        while j < length:
            for key, value in header_list[i].hashtbale.items():
                if header_list[j].hashtbale.get(key) and header_list[j].hashtbale[key] == value:
                    print value
                    print header_list[j].hashtbale[key]
                    redundacy += len(value)
                    redundacy += len(key)
                    del header_list[j].hashtbale[key]
            j += 1
        i += 1
    print redundacy
    print total_size
    print redundacy /float(total_size)

def storeToHashTable(header_elm,header):
    header.size += len(header_elm)
    obj = re.split(":",header_elm,1)
    #print len(obj)
    if len(obj) >= 2:
        header.hashtbale[obj[0]] = obj[1]

def printHeaderList(header_list):
   length = len(header_list)
   i = 0
   while i < length:
       print header_list[i].requestOrResponse
       for key,value in header_list[i].hashtbale.items():
           print key + " : " + value
       i += 1


def main():
    print "hello world!"
    filename = sys.argv[1] 
    f = open(filename,"a+")
    data = f.read()
#    print data
    matchObj = re.split("(---------- delimited .* ----------)\n",data,0)
    length = len(matchObj)
    print length
#print data
    header_list = []
    if matchObj:
        i = 1
        index = 0
        flag = 0
        while (i < length):
#            print elm
            if i % 2 == 0 and flag == 1:
                # split header into lines then store into class header
                headObj = re.split("\r\n",matchObj[i],0)     
                header  = Header()
                header.requestOrResponse = headObj[0]
                header.size += len(header.requestOrResponse)
                for header_elm in headObj:
                    if header_elm != "\r\n":
                        print "Header: " + header_elm
                        storeToHashTable(header_elm,header)
                    #store header to hash table
                header_list.append(header)
                index += 1
            else:
                obj = re.search("header",matchObj[i],0)
#                header_list[index] = header()
                if obj: 
                    flag = 1
                else:
                    flag = 0
            i += 1

    else:
        print "No match"

    printHeaderList(header_list)

    headerDiff(header_list)


if __name__ == "__main__":
   main()

