#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys, string, locale
from optparse import OptionParser


locale.setlocale(locale.LC_ALL, '')

class getlines:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()
        
	
    def getList(self):
        list1=list(self.lines)
        return list1
    



def main():
    version_msg = "%prog Alpha"
    usage_msg = """%prog [OPTION]... FILE 
Comparing the lines from two files or from standard input."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1", 
                      action="store_true",dest="Col1"
                      , default=False,
                      help="Hide the first column of the output")
                      
    parser.add_option("-2",
                      action="store_true", dest="Col2"
                      , default=False,
                      help="Hide the second column of the output")
                      
    parser.add_option("-3",
                      action="store_true", dest="Col3"
                      , default=False,
                      help="Hide the third column of the output")
                      
    parser.add_option("-u", 
                      action="store_true", dest="sort"
                      , default=False,
                      help="output NUMLINES lines (default 1)")
                      
                      
                      
                      
    options, args = parser.parse_args(sys.argv[1:])
    
    input_file1 = args[0]
    input_file2 = args[1]
    

    def printSpace(num, str):
        if num==1:
            if options.Col1==True:
                return
        elif num==2:
            if options.Col2==True:
                return
            if options.Col1==False:
                sys.stdout.write("\t")
        elif num==3:
            if options.Col3==True:
                return
            if options.Col1==False:
                sys.stdout.write("\t")
            if options.Col2==False:
                sys.stdout.write("\t")

        sys.stdout.write(str)  
	
    if len(args) != 2:
        parser.error("The number of operands is not correct!")
    
    try:
        if input_file1=="-":
            file1=list(sys.stdin.readlines())
        else:
            lines1=getlines(input_file1)
            file1=list(lines1.getList())

        if input_file2=="-":
            file2=list(sys.stdin.readlines())
        else:
            lines2=getlines(input_file2)
            file2=list(lines2.getList())
    except:
        parser.error("Something wrong happened when processing the files!")

    if options.sort==False:
        if file1!= sorted(file1) or file2!=sorted(file2):
            parser.error("Some files are not sorted :(")
    
    file1.sort()
    file2.sort()  #Sort the files anyways
    
    arr1={}
    arr2={}
    
    
    for item in file1:
    	if item in arr1:
    		arr1[item]+=1;
    		
    	else:
    		arr1[item]=1;
    
    
    
    for item2 in file2:
    	if item2 in arr2:
    		arr2[item2]+=1;
    	else:
    		arr2[item2]=1;
    		
    		
    uniqueFile1=list(set(file1))
    uniqueFile2=list(set(file2))

    
    uniqueFile1.sort()
    uniqueFile2.sort()
    
    
	
    try:
        for i in uniqueFile1:
            firstCol=1
            thirdCol=0
            if i in arr2:
                thirdCol= min(arr1[i],arr2[i])
                firstCol= max(0,arr1[i]-arr2[i])
            else:
                firstCol=arr1[i]
            for counter1 in range (firstCol):
                printSpace(1,i)
            for counter2 in range (thirdCol):
                printSpace(3,i)



        for j in uniqueFile2:
            secondCol=0
            if j in arr1:
                secondCol= max(0,arr2[j]-arr1[j])
            else:
                secondCol=arr2[j]
            for counter3 in range (secondCol):
                printSpace(2,j)
			
    except IOError:
        parser.error("There's an IO error somewhere!") 

     


if __name__ == "__main__":
    main()
