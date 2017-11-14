import re
import sys

d = {}


def add(input_command):
    global street_name, GPS_coordinate
    if not re.findall(r'"(.*)"', input_command):
        sys.stderr.write('\nError: Invalid input.\n')
    else:
        street_name = re.findall(r'"(.*)"', input_command)
        GPS_coordinate = re.findall('\([-]*\d\,[-]*\d\)', input_command)
        if len(GPS_coordinate)<=1:
            sys.stderr.write('Error: Incomplete coordinates, no end point\n')
        if street_name[0] not in d:
            d[street_name[0]] = GPS_coordinate
        else:
            sys.stderr.write('Error: The street is already exit.\n')


def change(input_command):
    if not re.findall(r'"(.*)"', input_command):
        sys.stderr.write( 'Error: Invalid input2.\n')
    else:
        street_name = re.findall(r'"(.*)"', input_command)
        if street_name[0] in d:
            GPS_coordinate = re.findall('\([-]*\d\,[-]*\d\)', input_command)
            d[street_name[0]] = GPS_coordinate
            if len(GPS_coordinate)<=1:
                sys.stderr.write('Error: Incomplete coordinates, no end point\n')
        else:
            sys.stderr.write('Error: you should input exist Street name.\n')
    



def remove(input_command):
    if not re.findall(r'"(.*)"', input_command):
        sys.stderr.write( 'Error: Invalid input3.\n')
    else:
        remove_street = re.findall(r'"(.*)"', input_command)
        if remove_street[0] in d:
            d.pop(remove_street[0])
        else:
            sys.stderr.write('Error: you should input exist Street name.\n')


def graph():
    global ef
    d_value = {}
    d_2 = {}
    biglist = []
    group_number = []
    list_number_all=[]
    for (k, v) in dict.items(d):
        str_v = ''.join(v)
        GPS_coordinate_list = re.findall('[-]*\d', str_v)
        list_number = []
        for x in GPS_coordinate_list:
            GPS_coordinate_v = int(x)
            list_number.append(GPS_coordinate_v)
        d_value[k] = list_number
        n = 0
        list_ABCD = []
        while n + 3 <= (len(list_number) - 1):
            list_abcd = []
            A = list_number[n]
            B = list_number[n + 1]
            C = list_number[n + 2]
            D = list_number[n + 3]
            list_abcd.append(A)
            list_abcd.append(B)
            list_abcd.append(C)
            list_abcd.append(D)
            list_ABCD.append(list_abcd)
            n = n + 2
        group = len(list_ABCD)
        group_number.append(group)
        biglist.append(list_ABCD)
        for n in list_number:
            list_number_all.append(n)

    i = 0
    u=0
    o=0
    group_number_1=group_number[:]
    test=[]
    while i < (len(d) - 1):
        j = 0
        while j <= (group_number[i] - 1):
            x1 = biglist[i][j][0]
            x2 = biglist[i][j][2]
            y1 = biglist[i][j][1]
            y2 = biglist[i][j][3]
            w=i+1
            while w < len(biglist):
                y = 0
                while y < group_number[w]:
                    x3 = biglist[w][y][0]
                    x4 = biglist[w][y][2]
                    y3 = biglist[w][y][1]
                    y4 = biglist[w][y][3]
                    if ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)) != 0:
                        px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))
                        py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))
                        if ((px >= x1 and px <= x2) or (px <= x1 and px >= x2)) and ((py >= y1 and py <= y2) or (py <= y1 and py >= y2)):
                            if ((px >= x3 and px <= x4) or (px <= x3 and px >= x4)) and ((py >= y3 and py <= y4) or (py <= y3 and py >= y4)):
                                aa=(x1,y1,x2,y2,px,py)
                                cc=(x3,y3,x4,y4,px,py)
                                if aa not in test:
                                    group_number_summer1 = 0
                                    for g in range(0, i):
                                        group_number_summer1 = group_number_summer1 + group_number[g]
                                    location1 = (group_number_summer1+i)*2+j*2+2+u
                                    location2 = location1 + 1
                                    list_number_all.insert(location1, px)
                                    list_number_all.insert(location2, py)
                                    u=u+2
                                    group_number_1[i] = group_number_1[i] + 1
                                group_number_summer = 0
                                if cc not in test:
                                    for g in range(0, w):
                                        group_number_summer = group_number_summer + group_number[g]
                                    location3 = (group_number_summer+w)*2+y*2+2+u+o
                                    location4 = location3 + 1
                                    list_number_all.insert(location3, px)
                                    list_number_all.insert(location4, py)
                                    o=o+2
                                    group_number_1[w]= group_number_1[w] + 1
                                test.append(aa)
                                test.append(cc)
                    y = y + 1
                w = w + 1
            j = j + 1
        i = i + 1

    biglist = []
    z = 0
    h=0
    for n in group_number_1:
        list_ABCD = []
        while z + 3 <= ((n+1) * 2+h):
            list_abcd = []
            A = list_number_all[z]
            B = list_number_all[z + 1]
            C = list_number_all[z + 2]
            D = list_number_all[z + 3]
            list_abcd.append(A)
            list_abcd.append(B)
            list_abcd.append(C)
            list_abcd.append(D)
            list_ABCD.append(list_abcd)
            z += 2
        z=z+2
        h=h+(n+1)*2
        biglist.append(list_ABCD)

    i = 0
    k = 0
    vertex = set([])
    edge = set([])
    V = {}
    E = {}
    number = 1
    while i < (len(d) - 1):
        j = 0
        while j <= (group_number_1[i] - 1):
            x1 = biglist[i][j][k]
            x2 = biglist[i][j][k + 2]
            y1 = biglist[i][j][k + 1]
            y2 = biglist[i][j][k + 3]
            w=i+1
            while w < len(biglist):
                y = 0
                while y <= (group_number_1[w] - 1):
                    x3 = biglist[w][y][k]
                    x4 = biglist[w][y][k + 2]
                    y3 = biglist[w][y][k + 1]
                    y4 = biglist[w][y][k + 3]
                    if ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)) != 0:
                        px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / (
                            (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))
                        py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / (
                            (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))
                        if ((px >= x1 and px <= x2) or (px <= x1 and px >= x2)) and (
                                    (py >= y1 and py <= y2) or (py <= y1 and py >= y2)):
                            if ((px >= x3 and px <= x4) or (px <= x3 and px >= x4)) and (
                                        (py >= y3 and py <= y4) or (py <= y3 and py >= y4)):
                                vertex.add((x1, y1))
                                vertex.add((x2, y2))
                                vertex.add((x3, y3))
                                vertex.add((x4, y4))
                                vertex.add((px, py))
                                for ee in vertex:
                                    if ee not in E:
                                        E[ee] = number
                                        number = number + 1
                                intersection = E[(px, py)]
                                point1 = E[(x1, y1)]
                                point2 = E[(x2, y2)]
                                point3 = E[(x3, y3)]
                                point4 = E[(x4, y4)]
                                if intersection!=point1:
                                    edge.add((intersection, point1))
                                if intersection != point2:
                                    edge.add((intersection, point2))
                                if intersection != point3:
                                    edge.add((intersection, point3))
                                if intersection != point4:
                                    edge.add((intersection, point4))
                    y = y + 1
                w = w + 1
            j = j + 1
        i = i + 1
    Edge=set([])
    for c in edge:
        if c[0]>c[1]:
            p=c[0]
            q=c[1]
            temp=q
            q=p
            p=temp
            Edge.add((p,q))
        else:
            Edge.add((c[0],c[1]))

    for (k, v) in E.items():
        V[v] = k
    sys.stdout.write('V={\n')
    for (k, v) in V.items():
        sys.stdout.write(' ' + str(k) + ':  ' + str(v) + '\n')
    sys.stdout.write('}')

    sys.stdout.write('\n'+'E={\n')
    n=len(Edge)
    n1=0
    for ef in Edge:
        if n1<(n-1):
            sys.stdout.write('<' +str(ef[0])+','+str(ef[1])+'>'+','+'\n')
            n1=n1+1
    if len(Edge)!=0:
        sys.stdout.write('<' + str(ef[0]) + ',' + str(ef[1]) + '>' +'\n'+ '}')
    else:
        sys.stdout.write('}')


if __name__ == '__main__':
    while True:                  
        input_command = raw_input()
        command = re.findall(r'^\w', input_command)
        if command == ['a']:
            add(input_command)
        elif command == ['c']:
            change(input_command)
        elif command == ['r']:
            remove(input_command)
        elif command == ['g']:
            graph()
        elif input_command == '':
            pass
        else:
            sys.stderr.write('Error you should print in "a","c","r" or "g"\n')
