import os
import sys
import csv
import shutil
import json

GRADE_INDEX = 3

#utility class
class Criteria:
    def __init__(self, c, n, p):
        self.crit = c + "? [Y/n]: "
        self.note = n
        self.points = p

class SubmissionGrader:
    def __init__(self, lab_num, dir, s):
        self.lab = lab_num
        self.dir = dir
        self.student = s
        if(self.student.partner):
            self.rubric = json.load(open("rubrics/program"+str(lab_num)+".json"))
        else:
            self.rubric = json.load(open("rubrics/lab"+str(lab_num)+".json"))
        if "driver" in self.rubric:
            print("Copying", self.rubric["driver"]," => ",dir+"/"+self.rubric["driver"], "...")
            shutil.copyfile("drivers/"+self.rubric["driver"], dir+"/"+self.rubric["driver"])
            print("Original driver code copied into repo")
        self.comments = []

    #template method
    def grade(self):
        self.gradefile = open("grades.txt", "a")
        self.points = self.rubric['points']
        pwd = os.getcwd()
        os.chdir(self.dir)
        if(self.initSubmission() and self.testRuntime()):
            self.testInspection()
        else:
            self.points = 0
        self.endSubmission()
        os.chdir(pwd)
        return self.student.graderecord

    def initSubmission(self):
        self.gradefile.write("\n=====================\n")
        self.gradefile.write(self.student.name+"\n")
        self.gradefile.write("Total points possible: " + str(self.points)+"\n")

        print("commit hash:\t\t" + self.student.hash)
        okay = input("\n -- Please verify commit hash is in the correct format [Y/n]")
        if(okay.lower() == 'y'):
            os.system("git checkout " + self.student.hash)
        else:
            self.gradefile.write("Incorrect hash submission on MyCourses. Resubmit ASAP\n")
            self.comments.append("Incorrect hash submission on MyCourses. Resubmit ASAP.")
            self.invalidSubmission()
            return False

        os.system("ls")
        if(input("\n -- Are all required files present (Y/n)? ").lower() != 'y'):
            self.gradefile.write("\tMissing files in your repo. Resubmit ASAP.\n")
            self.comments.append("Missing files in your repo. Resubmit ASAP.")
            self.invalidSubmission()
            return False
        if(input("\n -- Repo does not include binary files (*.o, executable) (Y/n)? ").lower() != 'y'):
            self.gradefile.write("\tRepo must not include binary files (*.o, executable).\n")
            self.deductPoints("Repo must not include binary files (*.o, executable)", -1)
            os.system("make clean")
        return True

    def testRuntime(self):
        input("\n\nThe following grading criteria are runtime operations. Press any key to continue....")
        os.system(self.rubric['run'])
        prompt = "\n\n -- Does their code run, and give output? [Y/n]"
        if(input(prompt).lower() != 'y'):
            print("Code does not compile. Unable to evaluate.")
            self.gradefile.write("Code does not compile. Unable to evaluate.\n")
            self.gradefile.write("In the future, comment out non-working code to get points for the things that do work.\n")
            self.comments.append("Code does not compile. Unable to evaluate.")
            return False
        for c in self.rubric['runtime']:
            if(input("\n-- " + c['crit'] + " [Y/n]? ").lower() != 'y'):
                self.deductPoints(c['note'], c['points'])

        if("memcheck" in self.rubric):
            os.system("make memcheck")
            prompt = "\n\n -- Does their code have any memory leaks? [Y/n]"
            if(input(prompt).lower() != 'y'):
                print("Memory Leaks")
                self.gradefile.write("Code does not compile. Unable to evaluate.\n")
                self.gradefile.write("In the future, comment out non-working code to get points for the things that do work.\n")
                self.comments.append("Code does not compile. Unable to evaluate.")

        return True

    def testInspection(self):
        input("\nFor the following grading criteria, please open their project in a text editor.\n\t Repo:\t"+self.student.repo_url+"\n\nPress any key when ready...")
        for c in self.rubric['inspect']:
            if(input("\n-- " + c['crit'] + " [Y/n]? ").lower() != 'y'):
                self.deductPoints(c['note'], c['points'])
        return True

    def endSubmission(self):
            self.gradefile.write("Final Score: " + str(self.points) + "\n")
            if(self.student.partner):
                self.gradefile.write(" Partners: "+ self.student.partner + "\n" +"\n".join(self.comments))
            self.gradefile.write("===============")
            self.gradefile.close()
            index = GRADE_INDEX
            if(self.points < 0):
                self.points = 0
            self.student.graderecord[index] = str(self.points)
            #print("Should be SMART_TEXT or blank:", self.graderecord[index+2])
            self.student.graderecord[index+2] = ""
            #print("Should be Comments:", self.graderecord[index+3])
            if(self.student.partner):
                self.student.graderecord[index+3] = "<p> Partners: "+ self.student.partner +"<br/>"+ "<br/>".join(self.comments) + "</p>"
            else:
                self.student.graderecord[index+3] = "<p> "+ "<br/>".join(self.comments) + "</p>"
            self.student.graderecord[index+4] = "HTML"

    ####################    Utility Functions   #################
    def invalidSubmission(self):
        print("=======Invalid submission=======")
        print("DO NOT grade this until the student fixes their submission.")
        print("Post a 0 in mycourses until the assignment is fixed.")
        print("The standard late penalty applies from the time you post the grade")
        print(" + -1 for incorrect submission.")

    def deductPoints(self, msg, deduct):
        print("\t "+ str(deduct) + "\t" + msg)
        self.gradefile.write("\t "+ str(deduct) + "\t" + msg + "\n")
        self.points += deduct
        self.comments += [str(deduct)+" - " + msg]
