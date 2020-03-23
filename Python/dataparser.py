import os, json

"""
	Opens the files storing information about the Database Nodes being added,
	and takes the data and puts it into a .json formatted file
"""

listed_ = []
node_names = []
IdNumber = []
d = 1

for i in os.listdir('/home/runner/FinishedSecretOutlier'):
	if 'Node Information #' in i:
		listed_.append(i)

for i in range(len(listed_)):
	data = open(listed_[i],'r').read()
	node_names.append(data)

for i in range(len(node_names)):
	if str(d) in node_names[i]:
		index = node_names[i].find(str(d))
	
	IdNumber.append(node_names[i][index])
	node_names[i] = node_names[i].replace('\n','')
	node_names[i] = node_names[i].replace(IdNumber[i],'')
	node_names[i] = node_names[i].replace('Added Database Node ','')
	data_ = {'NodeNames':node_names,'NodeIds':IdNumber}
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
