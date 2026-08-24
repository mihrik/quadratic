N, M = map(int, input().split())
K = int(input())
wind = []
for i in range(K):
    minx, maxx, miny, maxy = map(int, input().split())
    wind.append([minx, maxx, miny, maxy])

fasad = [[0 for x in range(N)] for y in range(M)]

way = []
marker = 1
for i in wind:
    if (i[0] < 0 or i[1] < 0 or i[2] < 0 or i[3] < 0 or i[1] < i[0] or i[3] < i[2]):
        marker = 0
        break
    
    times_N = i[1] - i[0]
    times_M = i[3] - i[2]

    M_line = M - 1 - i[2]
    N_line = i[0]
    if M_line + times_M >= 2 * M or N_line + times_N >= N:
        marker = 0
        break

    for p in range(times_M):
        for j in range(times_N):
            way.append([M_line-p, N_line + j])
            
for i in way:
    
    if way.count(i) > 1:
        marker = 0
        break

if marker == 1:
    print("correct")
else:
    print("broken")
