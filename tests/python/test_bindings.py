import ktk
import numpy as np

def test_1():
    assert ktk.my_test_fun(5) == 5**2

def test_2():
    assert ( ktk.my_eigen_fun(2, 7) == np.array([2,0,0]) ).all()
