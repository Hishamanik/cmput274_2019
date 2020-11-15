# Read the input
a, b, c = map(int, input().split())


# Solve the problem
average = int((a+b+c)/3)
a = abs(a -average)
b = abs(b-average)
c = abs(c-average)

# Output the result
print(a,b,c)