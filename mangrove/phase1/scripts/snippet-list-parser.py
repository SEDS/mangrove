#!/opt/local/bin/python2.7

f = open('../juliet-logs/snippet-list.txt', 'r').read().splitlines()
snippet_maps={};
for line in f:
   line_arr=line.split(' ')
   if line_arr[0] in snippet_maps:
      snippet_maps[line_arr[0]] +=1
   else:
      snippet_maps[line_arr[0]] =1


print snippet_maps