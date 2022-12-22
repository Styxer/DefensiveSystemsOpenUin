import importlib.util
import inspect
import random
from functools import wraps


ARG_UPPER_BOUND = 100000

def decotitle(method, code):
    # Preserve function signature
    @wraps(method)
    def wrapped(*args, **kwargs):
        eval(code)
        return method(*args, **kwargs)
    return wrapped

def add_class_code(target_class, code_to_add):
    for func_name in dir(target_class):
        # Get method, make sure it's callable, and wrap it.
        class_func = getattr(target_class, func_name)
        if callable(class_func) and not func_name.startswith('__'):
            new_method = decotitle(class_func, code_to_add)
            setattr(target_class, func_name, new_method)

def call_with_random_ints(to_call):
    func_signature = inspect.signature(to_call)
    # Generate random parameter values, and skip self.
    args_ls = [random.randint(0, ARG_UPPER_BOUND) for _ in range(len(func_signature.parameters))]
    return to_call(*args_ls)

def call_methods(target_class):
    instance = call_with_random_ints(target_class)
    for func_name in dir(instance):
        # Get method, make sure it's callable, and wrap it.
        class_func = getattr(instance, func_name)
        if callable(class_func) and not func_name.startswith("__"):
            call_with_random_ints(class_func)



if __name__ == "__main__":
     module_to_load = input("Enter python file name: ")
     code_to_add = input("Enter a python code: ")
     spec = importlib.util.spec_from_file_location("module_to_load", module_to_load)

      # Try load module
     try:
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
     except:
        print(f"Failed to load module from file {module_to_load}!")
        exit(0)
    
     classes = inspect.getmembers(module, inspect.isclass)  
     # Replace methods
     for name, cls_to_proc in classes:
        add_class_code(cls_to_proc, code_to_add)

    # Execute methods
     for name, cls_to_proc in classes:
        call_methods(cls_to_proc)