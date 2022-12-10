class BankAccount:
  def __init__(self, name, amt):
    self.name = name
    self.amt = amt
    
  def __str__(self):
    return f"Your account, {self.name}, has a balance of {self.amt} dollars."

# Create an instance of the BankAccount class
t1 = BankAccount("Bob", 100)

# Print the instance
print(t1)