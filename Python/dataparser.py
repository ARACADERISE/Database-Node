import os, json

"""
	Opens the files storing information about the Database Nodes being added,
	and takes the data and puts it into a .json formatted file
"""

listed_ = []
node_names = []
Action = []
IdNumber = []
d = 1
nums = ['1','2','3','4','5','6','7','8','9','0']

for i in os.listdir(os.path.abspath('.')):
	if 'Node Information #' in i:
		listed_.append(i)

if len(listed_) != 0:
	for i in range(len(listed_)):
		data = open(listed_[i],'r').read()
		node_names.append(data)

	for i in range(len(node_names)):
		if str(d) in node_names[i]:
			TOTAL_LENGTH = len(node_names[i])
			index = node_names[i].find(str(d))
			
		
		IdNumber.append(node_names[i][index])
		node_names[i] = node_names[i].replace('\n','')
		node_names[i] = node_names[i].replace(IdNumber[i],'')
		for n in nums:
			if n in node_names[i]:
				ind = node_names[i].find(n)
				node_names[i] = node_names[i].replace(node_names[i][ind],'')
				IdNumber[i]+=n
				if '12' in IdNumber:
					IIndex = IdNumber.index('10')
					IdNumber[IIndex+1]='11'
		Action.append(node_names[i])
		node_names[i] = node_names[i].replace('Added Database Node ','')
		data_ = {'Actions':Action,'NodeNames':node_names,'NodeIds':IdNumber}
		d+= 1

	with open('NodeData.json','w') as NodeData:
		NodeData.write(json.dumps(
			data_,
			indent=2,
			sort_keys=True
		))
		NodeData.flush()
		NodeData.close()

	for i in range(len(listed_)):
		os.remove(listed_[i])
