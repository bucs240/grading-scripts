# CS240 Grading Scripts
## Fall 2019

***

Each lab has its own grading rubric, stored in json files (rubrics folder). The correct rubric is called based on the lab number. To run the script, you must:
1. Download the submissions from MyCourses
2. Rename the folder to 'gradebook' after unzipping
3. Place it in the top level directory.
    * Just download all of them, and place them in the folder. You can select sections when you run the script.
4. Download the csv (comma delimited) for the assignment you want to grade.
    * Go to Full Grade Center > Work Offline
    * Select Selected Column and the Lab you want to grade
        * :warning: Make sure you check "Include comments for this Column"
    * Select `Comma` for "Delimiter Type"
    * Leave "Include Hidden Information" as `no`
    * Download the file and rename to "gc.csv"
    * Place it in the top level grading directory
5. Run the "main.py" script and pass the lab number and section you wish to grade
    * Example: `python3 main.py 1 A51`
6. The script will download all repos for that section, and begin grading.
    * If any repos were not downloaded or there was an error, you should get a message.
7. The script will run through each repo, asking you questions regarding the submission.
    * The first few labs will require you to look around at code. Most labs thereafter will just be based on unit tests, and you will only need to give the code a cursory glance.
8. The script produces 2 files:
    * A csv file with student scores and appropriate comments you can upload directly to MyCourses.
        * The csv file is truncated each time you run the script.
    * A text file with the same information, just in case soemthing goes wrong.
        * If the text file already exists, it will rename the file with the date-time appended, and create a new one. So if there is an existing grades.csv already there, it will not be deleted. That way you can skip through the first 5 submissions if there was some error with one of them, then continue with a new grading file.
9. Upload the grades.csv into MyCourses gradebook or copy and paste form the text file.

## TODO:
There are several improvements to be made to make things easier. Feel free to add ideas for features that will make this run smoother.
* multiple sections option
