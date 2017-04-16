import sys
import os
from itertools import *

#REQUIRES: the highest directory to be dealt with and moved to
#PURPOSE: This function will recursively move through all of the files and folders in the current directory (Depth First) and 
            #move all the files to the top directory and delete all the empty folders left behind
def moveUp(currentDir):
    myDirList = []
    for subdir, dirs, files in os.walk(currentDir):                                 #walk through the whole folder and file tree starting from the given root node
        if subdir not in myDirList:                                                 #create a list of all the directories visited
                myDirList.append(subdir)
        for file in files:
            if (not subdir == currentDir):
                print('Moving: ' + os.path.join(subdir, file))                      #print out each found filepath
                if (os.path.isfile(file)):                                          #If that file exists
                    i = 0
                    fileNameStart = ".".join(file.split('.')[:-1])
                    fileExtension = "."+"".join(file.split('.')[-1])
                    filename = fileNameStart + str(i) + fileExtension
                    while os.path.exists(filename):                                 #find a unique number ending for the file
                        i += 1
                        filename = fileNameStart + str(i) + fileExtension
                    os.rename(os.path.join(subdir, file), os.path.join(currentDir, filename)) #append a number and move this file to the top
                else:
                    os.rename(os.path.join(subdir, file), os.path.join(currentDir, file))   #move this file to the top
            
    myDirList.reverse()                                                             #reverse the order of the files found, we want to start cleaning at the bottom
    for myDir in myDirList:                                                         
        if (not os.listdir(myDir)):                                                 #check whether this folder is empty
            print ('Finishing Up In: ' + os.path.join(myDir))
            os.rmdir(myDir)                                                         #since the folder is empty, delete it (this function won't delete a non-empty folder)
        
#program starts here
if (len(sys.argv) > 1):                                                             
    currentDir =  sys.argv[1]                                                       #if there are parameters to the function call, get the first one and start there
else:
    currentDir = os.getcwd()                                                        #else, start work in the current directory
    
moveUp(currentDir)