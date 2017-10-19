import time
start_time = time.time()


digits = []
def digit_sum(n):
  multiplier = 10
  while True:
    if int(n / multiplier) == 1 and n % multiplier in range(0,10):
      remainder = n % multiplier
      digits.append(remainder)
      n = n - remainder
      n = n / 10
      if n in range (1,10):
        digits.append(n)
        break  
      multiplier = 10  
    if n != 10:
      multiplier += 10
  digitsum = 0
  for item in digits:
    digitsum += item
  return digitsum
print (digit_sum(5659596529))


print("--- %s seconds ---" % (time.time() - start_time))
