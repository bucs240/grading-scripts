class Student:
    def __init__(self, name, bnum, bmail, gu, repo, grade, partner=None, hash=None):
        self.name = name
        self.bnum = bnum
        self.github_username = gu
        self.repo_url = repo
        self.hash = hash
        self.graderecord = grade
        self.bmail = bmail
        self.partner = partner
