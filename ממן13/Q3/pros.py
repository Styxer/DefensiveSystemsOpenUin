stop_button = 's'
exit_button = 'n'

class User:
    def __init__(self, name, profession):
        self._name = name
        self._profession = profession


#region Professions
class Engineer(User):
    def __init__(self, name, engineer_type):
       super().__init__(name, f"{engineer_type} Engineer")
class Technician(User):
    def __init__(self, name):
      super().__init__(name, "Technician")

class Barber(User):
    def __init__(self, name):
        super().__init__(name, "Barber")

class Politician(User):
    def __init__(self, name):
        super().__init__(name, "Politician")
#endregion

#region Engineers Types
class ElectricalEngineer(Engineer):
    def __init__(self, name):
        super().__init__(name, "Electrical")

class ComputerEngineer(Engineer):
    def __init__(self, name):
        super().__init__(name, "Computer")

class MechanicalEngineer(Engineer):
    def __init__(self, name):
        super().__init__(name, "Mechanical")
#endregion

classes = {"User": User, "Engineer" : Engineer, "Technician" : Technician , 
           "Barber" : Barber,  "Politician" : Politician, "ElectricalEngineer" : ElectricalEngineer  , 
           "ComputerEngineer" : ComputerEngineer, "MechanicalEngineer" : MechanicalEngineer}


def select_base_class():
    if(input(f'press any key if you want to get the base class? else press {exit_button}') != f'{exit_button}'):
        base_Class = classes.get(input("Enter the base class name: "))
        if(base_Class is not None) :
            return (base_Class, )
        print("the class does not exist!")
    return () #return some rmpty tuple
   

if __name__ == "__main__":
   while(input(f'Enter anykey in order to start[enter {stop_button} in order to stop the program]!') != f'{stop_button}'):


