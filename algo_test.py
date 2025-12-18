#!/usr/bin/env python3

from pprint import pprint

sites = [
    [[534, 61], [0, 128, 128]],
    [[758, 542], [255, 255, 0]],
    [[681, 364], [128, 0, 0]],
    [[735, 537], [255, 0, 255]],
    [[735, 616], [128, 255, 0]],
    [[411, 763], [0, 128, 128]],
    [[466, 633], [0, 0, 255]],
    [[243, 570], [128, 255, 0]],
    [[927, 215], [128, 128, 128]],
    [[646, 767], [1, 27, 3]]
]

chunks_dimensions = 200
width_in_chunks = 5
height_in_chunks = 5
width = chunks_dimensions * width_in_chunks
height = chunks_dimensions * height_in_chunks

chunkArr = []
for i in range(0, height_in_chunks):
    chunkArr.append([])
    for j in range(0, width_in_chunks):
        chunkArr[i].append([])

for i in range(0, len(chunkArr)):
    print(chunkArr[i])

p = 0
while p < len(sites):
    sites[p].append(f"index {p}")
    x = sites[p][0][0]
    y = sites[p][0][1]
    print(f"{x} {y}")
    chunkArr[y // chunks_dimensions][x // chunks_dimensions].append(sites[p])
    p += 1

for i in range(0, height_in_chunks):
    print(f"Row {i}")
    print(chunkArr[i])
    print("\n\n\n")
