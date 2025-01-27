#!/usr/bin/python3
import sys

def main():
    raw = sys.stdin
    
    # Create 3x3 matrices initialized to zero
    m1 = [[0]*3 for _ in range(3)]
    m2 = [[0]*3 for _ in range(3)]
    m3 = [[0]*3 for _ in range(3)]
    
    # Read input and fill matrices m1 and m2
    for line in raw:
        matrix, pos, value = line.split("\t")#splits as a 0,0 10 then use pos[0] and pso[-1] to get the string 0 and 0 and use int for conversion
        match matrix:
            case "a":
                m1[int(pos[0])][int(pos[-1])] = int(value)
            case "b":
                m2[int(pos[0])][int(pos[-1])] = int(value)
    
    for i in range(len(m1[0])):
        for j in range(len(m2)):
            for k in range(len(m1)):
                m3[i][j] += m1[i][k] * m2[k][j]

    for l in range(len(m3)):
        for i in range(len(m3[l])):
            print(f"c\t{l},{i}\t{m3[l][i]}")
        print()  # Newline after each row

main()

