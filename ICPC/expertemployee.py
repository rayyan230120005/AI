class EmployeePerformanceES:
    def __init__(self):
        self.score = 0
        self.feedback = []
        
    def get_rating(self, question):
        while True:
            try:
                r = int(input(f"{question} (1-10): "))
                if 1 <= r <= 10:
                    return r
                print("Enter number between 1 to 10.")
            except:
                print("Invalid input!")

    def evaluate(self):
        print("\n" + "="*60)
        print("   EMPLOYEE PERFORMANCE EVALUATION EXPERT SYSTEM")
        print("="*60)
        
        name = input("\nEmployee Name: ").strip()
        
        productivity = self.get_rating("1. Productivity & Quality of Work")
        timeliness   = self.get_rating("2. Timeliness & Deadlines")
        teamwork     = self.get_rating("3. Teamwork & Collaboration")
        initiative   = self.get_rating("4. Initiative & Innovation")
        attendance   = self.get_rating("5. Attendance & Punctuality")
        
        self.score = (productivity + timeliness + teamwork + initiative + attendance) // 5
        
        print("\n" + "="*60)
        print(f"PERFORMANCE REPORT - {name.upper()}")
        print("="*60)
        print(f"Overall Score      : {self.score}/10")
        
        if self.score >= 9:
            print("Rating             : Excellent")
            print("\nRecommendations:")
            print("• Outstanding performer")
            print("• Ready for promotion & higher responsibilities")
        elif self.score >= 7:
            print("Rating             : Good")
            print("\nRecommendations:")
            print("• Solid performer")
            print("• Minor improvements suggested")
        elif self.score >= 5:
            print("Rating             : Average")
            print("\nRecommendations:")
            print("• Needs improvement")
            print("• Recommend training & mentoring")
        else:
            print("Rating             : Poor")
            print("\nRecommendations:")
            print("• Below expectations")
            print("• Performance Improvement Plan (PIP) recommended")
        
        print("="*60)

# Run
if __name__ == "__main__":
    emp = EmployeePerformanceES()
    emp.evaluate()