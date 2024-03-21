import sys
import numpy as np

baseList = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], dtype=np.float64)

showList = baseList
showList = baseList / 9

hello = "".join(str(x) + ", " for x in showList)

print(hello)
