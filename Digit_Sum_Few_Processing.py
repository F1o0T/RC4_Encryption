import time
start_time = time.time()

def digit_sum(number):
  string = str(number)
  Sum_box = 0
  for item in string:
    Sum_box += int(item)
  return Sum_box
print (digit_sum(5659596529))

print("--- %s seconds ---" % (time.time() - start_time))
