#!/usr/bin/env python3

a = [1] * 10
print(a)
a[1] = 10
print(a)

a = [[]] * 10
print(a)
a[1].append(10)
print(a)

a = []
for i in range(10):
    a.append([])
a[1].append(10)
print(a)
'''
[1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
[1, 10, 1, 1, 1, 1, 1, 1, 1, 1]
[[], [], [], [], [], [], [], [], [], []]
[[10], [10], [10], [10], [10], [10], [10], [10], [10], [10]]
[[], [10], [], [], [], [], [], [], [], []]
'''