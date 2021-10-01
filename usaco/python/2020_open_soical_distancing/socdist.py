import sys

with open("socdist.in", "r") as fin:
  lines = fin.readlines()

n, m = map(int, lines[0].split())
intervals = []
for i in range(m):
    intervals.append(list(map(int, lines[1+i].split())))

intervals.sort()

def verify(gap, n, m, intervals):
  count = 0
  prev = 0
  for i in range(m):
    if i ==  0 or (intervals[i][0] - prev) >= gap:
      increased = (intervals[i][1] - intervals[i][0])//gap
      prev = intervals[i][0] + increased * gap
      count += increased + 1
    else:
      increased = (intervals[i][1] - prev)//gap
      prev += increased * gap
      count += increased
  if count >= n:
    return True
  else:
    return False

left = 0
right = intervals[m-1][1] - intervals[0][0]

result = 0
while left <= right:
  middle = left + (right - left)//2
  if verify(middle, n, m, intervals):
    left = middle + 1
    result = middle
  else:
    right = middle - 1

with open('socdist.out', 'w') as fout:
  fout.write(str(result) + '\n')
