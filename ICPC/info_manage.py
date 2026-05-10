class InformationManagementES:
    def __init__(self):
        self.knowledge_base = {
            "leave": {
                "answer": "You can apply for leave through the HR portal.\nAnnual Leave: 21 days | Sick Leave: 12 days",
                "category": "HR"
            },
            "salary": {
                "answer": "Salary slips are available in the Payroll section of the employee portal.\nSalary is credited on the 1st of every month.",
                "category": "Finance"
            },
            "it_reset": {
                "answer": "For password reset, go to https://password.company.com or contact IT Helpdesk at Ext: 456",
                "category": "IT"
            },
            "meeting": {
                "answer": "Use Microsoft Teams for booking meeting rooms.\nAll rooms are visible in the 'Book a Room' tab.",
                "category": "General"
            },
            "policy": {
                "answer": "All company policies are available in the shared drive → HR → Policies folder.",
                "category": "HR"
            },
            "laptop": {
                "answer": "For laptop issues, raise a ticket in ServiceNow portal.",
                "category": "IT"
            }
        }

    def search(self):
        print("\n" + "="*55)
        print("   INFORMATION MANAGEMENT EXPERT SYSTEM")
        print("="*55)
        print("Topics: leave, salary, password, meeting, policy, laptop")
        
        while True:
            query = input("\nWhat information do you need? (or type 'exit'): ").strip().lower()
            
            if query == 'exit':
                break
                
            found = False
            for key in self.knowledge_base:
                if key in query or query in key:
                    data = self.knowledge_base[key]
                    print(f"\n✅ Found in {data['category']} Category:")
                    print(data['answer'])
                    found = True
                    break
            
            if not found:
                print("\n❌ Sorry, I don't have information on that topic yet.")
                print("Try: leave, salary, it_reset, meeting, policy, laptop")

# Run
if __name__ == "__main__":
    info_system = InformationManagementES()
    info_system.search()