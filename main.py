from bin import grader
from bin import submission
#import pdb; pdb.set_trace()
import os
import sys
import csv
import shutil
from datetime import datetime

SEMESTER = "fall19"
ORG="https://github.com/bucs240"
class Grader:
    def __init__(self, lab, semester, section):
        self.section = section
        os.chdir(sys.path[0])
        self.semester = semester
        self.lab = int(lab)
        self.gradescsv = []
        with open("gc.csv", newline='', encoding='utf-8-sig') as gc:
            reader = csv.reader(gc, dialect='unix')
            self.header = next(reader)
            print("HEADER:",self.header)
            [self.gradescsv.append(r) for r in reader]
        self.parseGithubUsers()

    def __str__(self):
        ostr = section + ":" + str(lab)
        for s in students:
            ostr += "\n"+s.name + " -- " + s.repo_url
        return ostr

    def parseGithubUsers(self):
        with open("github.csv", newline='') as csvf:
            subs = csv.reader(csvf, dialect='unix')
            self.students = []
            for row in subs:
                if(row[2] == self.section):
                    bmail = row[1].lower()
                    name = row[3] + ' ' + row[4]
                    bnum = row[5].replace("-", "").replace(" ", "").lower().replace("b", "")
                    github = row[6]
                    self.createStudents(bmail, name, bnum, github)

    def submissions(self):
        os.chdir(sys.path[0])
        os.system("mkdir submissions")
        os.chdir("submissions")

        print("Downloading repositories for", len(self.students),"students:")
        for student in self.students:
            print("\t Cloning", student.name, "repo from: ",student.repo_url)
            os.system("git clone " + student.repo_url)

        print("Verifying cloned repositories...")
        #get expected directories based on students list vs actual downloaded directories
        expected_dir_list = [student.repo_url.replace(ORG+"/", '') for student in self.students]
        list_folders = [f for f in os.listdir(os.getcwd()) if os.path.isdir(os.path.join(os.getcwd(), f))]
        print("=" * 16, "Program Report", "=" * 16)

        #compare expected with actual
        if sorted(list_folders) == sorted(expected_dir_list):
            print("All repositories pulled successfully!")
        else:
            err_count = 0
            for d in expected_dir_list:
                if d not in list_folders:
                    print("Expected repo", d, "was not cloned...")
                    err_count += 1
            if err_count != 0:
                print("!!!ATTENTION:", err_count,"repositories were not pulled due to errors!!!")
            else:
                print("An error was detected, but all repositories pulled successfully. Please review!")
        os.chdir(sys.path[0])

    def parseSubmission(self, student, submission_files):
        hash = None
        for f in submission_files:
            if student.bnum in f:
                submission = open("gradebook/"+f, 'r').read()
                if(submission):
                    #strip out tags and whitespace from submission
                    start = submission.find("Submission Field:")+len("Submission Field:")
                    end = submission.find("Comments:")
                    content = submission[start:end]
                    tag = content[content.find("<")+1:content.find(">")]
                    while(tag):
                        content = content.replace(tag, '')
                        tag = content[content.find("<"):content.find(">")+1]
                    hash = content.strip()
        return hash

    def grade(self):
        list_folders = [os.path.join(os.getcwd()+"/submissions", f) for f in os.listdir("submissions/") if os.path.isdir(os.path.join(os.getcwd()+"/submissions", f))]
        #get a list of submission files
        submission_files = [f for f in os.listdir("./gradebook/")]
        #for each folder, match with student, and run grading script
        if(os.path.exists("grades.txt")):
            os.rename("grades.txt", "grades"+datetime.now().strftime("%m-%d-%Y--%H-%M-%S")+".txt")
        for d in list_folders:
            submission = None
            #TODO breaks for programs
            for s in self.students:
                if s.repo_url.replace(ORG+'/', '') in d:
                    submission = s
                    break
            if(submission):
                print("\n======= Submission for", submission.name, "(", submission.repo_url, ") ========")
                if input("Do you want to grade this student? (Y/n): ").lower().strip() == 'y':
                    hash = self.parseSubmission(submission, submission_files)
                    if(hash):
                        print("Grading ", submission.name, "...")
                        submission.hash = hash
                        submission.graderecord = grader.SubmissionGrader(self.lab, d, submission).grade()
                        input("Grading for " + submission.name + " complete. Enter key to continue...")
                    else:
                        input("No submission found for " + submission.name + ". Double check this is correct.\n Enter key to continue...")
                else:
                    print("\t\tGrading for", submission.name, "skipped...")

    def writeCSV(self):
        csvrows = [self.header]
        for s in self.students:
            csvrows.append(s.graderecord)
        with open("gc-graded.csv", 'w', newline='') as gcsv:
            csv.writer(gcsv, dialect="unix").writerows(csvrows)


class LabGrader (Grader):
    def __init__(self, lab, semester, section):
        super().__init__(lab, semester, section)

    def createStudents(self, bmail, name, bnum, github):
        for i in range(len(self.gradescsv)):
            if(self.gradescsv[i][2] == "b"+bnum):
                repo_url = ORG+"/lab-"+str(self.lab)+"-"+self.semester+"-"+github
                grades_row = self.gradescsv[i]
                self.students.append(submission.Student(name, bnum, bmail, github, repo_url, grades_row))

class ProgramGrader (Grader):
    def __init__(self, lab, semester, section):
        super().__init__(lab, semester, section)

    def createStudents(self, bmail, name, bnum, github):
        for i in range(len(self.gradescsv)):
            if(self.gradescsv[i][2] == "b"+bnum):
                grades_row = self.gradescsv[i]
        partners = "prog"+str(self.lab)+".csv"
        with open(partners, newline='') as csvf:
            teams = csv.reader(csvf, dialect='unix')
            for t in teams:
                if(t[1] == bmail):
                    repo_url = t[2].replace(".git", "")
                    if(repo_url[-1] == "/"):
                        repo_url = repo_url[:-1]
                    partners = t[3] + ", " + t[4]
                    self.students.append(submission.Student(name, bnum, bmail, github, repo_url, grades_row, partners))

def main():
    print("Have you done the following?:")
    print("\t>Downloaded the zipped text submissions from blackboard?")
    print("\t>Unzipped and renamed the gradebook folder to 'gradebook' in the lab directory you want to grade?")
    input("Press enter when ready...")
    if(len(sys.argv) != 3):
        print("ERROR\n\tUsage: main.py <lab #> <section>")
        print("\tExample: main.py 1 A51")
        raise Exception("Incorrect usage")
    if(os.path.isdir("./submissions")):
        shutil.rmtree("./submissions")
    prog = input("Is this a program or a lab? [P/l]")
    if(prog.lower() == 'p'):
        grader = ProgramGrader(sys.argv[1], SEMESTER, sys.argv[2])
    else:
        grader = LabGrader(sys.argv[1], SEMESTER, sys.argv[2])
    #download submissions
    grader.submissions()
    #grade submissions for thats ection and lab
    grader.grade()
    grader.writeCSV()
    input("All submissions for section " + sys.argv[2] + " have been graded. Press any key to remove the submissions folder.")
    #once all submissions have been graded, remove submission folder
    shutil.rmtree("./submissions")

if __name__ == '__main__':
    main()
