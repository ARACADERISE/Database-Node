import os, json #struct

# will be used later on when bigger files are generated
#try:
#	from tqdm import tqdm
#except ImportError:
#	os.system('pip install tqdm')
#	from tqdm import tqdm

"""
	Opens the files storing information about the Database Nodes being added,
	and takes the data and puts it into a .json formatted file
"""

# For the Nodes
listed_ = []
node_names = []
Action = []
IdNumber = []
d = 1
nums = ['1','2','3','4','5','6','7','8','9','0']
ADDINFO = ''
DATA = []
AllAddedFiles = []
FoundFiles = []
dirs = [os.listdir(os.path.abspath('.'))]

# For the Eras
era_types = ['wro','ro','wo','da'] # this is needed so we can parse through the files
listed__ = []
era_data = []
era = []
era_one = ''
AddedFiles = []
files = []
SaveFiles = []

# Default node storage Storage
StorageFiles = []
storageData = []
storageAmmounts = [10000,20000, 20000]
titles = ['File Storage','String Storage','Integer Storage']
UpdateStorageFile = ''
DATA_ = {}
UpdateStorageFile = []

for i in os.listdir(os.path.abspath('.')):
	# This will parse files made for setting up the Database Nodes
	if 'Node Information #' in i:
		listed_.append(i)
	
	# This will parse files made for setting up the Era
	if 'Era Setup #' in i:
		listed__.append(i)
	
	# This will parse files that set up the Nodes storage
	if not 'UPDATE' in i and 'STORAGE' in i:
		StorageFiles.append(i)
	
	# This will parse files that update the ndes storage
	if 'UPDATESTORAGE' in i:
		UpdateStorageFile.append(i)

# This is useless but oh well
if len(StorageFiles) != 0:
	for i in range(len(StorageFiles)):
		openStorageFile = open(StorageFiles[i],'r').read()
		storageData.append(openStorageFile)

	for i in range(len(storageData)):
		storageData[i] = storageData[i].replace('\n','')
	#copy = storageData

	for i in range(len(storageData)):
		for b in titles:
			storageData[i] = storageData[i].replace(b,'')
		for x in storageAmmounts:
			storageData[i] = storageData[i].replace(': '+str(x),'')
			storageData[i] = storageData[i].replace('\t','')
			#break
	
	if len(UpdateStorageFile) != 0:
		info = []
		foundSize = []
		lookFor = ['INTEGER STORAGE','FILE STORAGE','STRING STORAGE']
		appendFound = []
		for i in UpdateStorageFile:
			info.append(open(i,'r').read())

		for i in range(len(UpdateStorageFile)):
			os.remove(UpdateStorageFile[i])
		
		for i in range(len(UpdateStorageFile)):
			UpdateStorageFile[i] = UpdateStorageFile[i].replace('UPDATESTORAGE-','')
		
		for x in info:
			for d in storageAmmounts:
				if str(d) in x:
					foundSize.append(str(d))
					break
		for i in range(len(info)):
			info[i] = info[i].replace(foundSize[i],'')
			info[i] = info[i].replace(' to ','')
			for x in lookFor:
				if x in info[i]:
					info[i] = info[i].replace(x,'')
					appendFound.append(x)
		
		for i in storageData:
			i = i.replace(':','')
			DATA_.update({i:['FILE STORAGE -> %d' % storageAmmounts[0], 'STRING STORAGE -> %d' % storageAmmounts[1], 'INTEGER STORAGE -> %d' % storageAmmounts[2]]})

		for i in UpdateStorageFile:
			if i in DATA_:
				for x in range(len(DATA_[i])):
					for d_ in appendFound:
						if d_ in DATA_[i][x]:
							DATA_[i][x] = DATA_[i][x].replace(foundSize[0],info[0])
							break

		for i in range(len(UpdateStorageFile)):
			name = UpdateStorageFile[i]
			UpdateStorageFile[i] = UpdateStorageFile[i]+'UPDSTG'

			with open(UpdateStorageFile[i],'w') as UpdStg:
				UpdStg.write('NODE: %s\n\tFROM %d\n\tTO %d' % (name,int(foundSize[i]),int(info[i])))
				UpdStg.flush()
				UpdStg.close()
		
		#index = None
		#for d in storageAmmounts:
		#	if str(d) in info:
		#		numberFound = d
		#		info = info.replace(str(d),'')
		#		info = info.replace('to','')
		#		index = storageAmmounts.index(d)
		

if len(listed__) != 0:
	for i in range(len(listed__)):
		open_ = open(listed__[i],'r').read()
		if open_ in era_data:pass
		else:era_data.append(open_)
	
	for i in range(len(era_data)):
		if era_data[i][0] != 'w':
			for x in era_types:
				if x in era_data[i]:
					if x in era:pass
					else:era.append(x)
		else:
			era.append('wro')

		era_data[i] = era_data[i].replace(era[i],'')
		era_data[i] = era_data[i].replace('\n','')
		if 'ta' in era_data[i]:
			era_data[i] = era_data[i].replace('ta','data')
		
		
	
	data___ = {'Era Types':era,'Era Used For':era_data}
	
	with open('EraData.json','w') as EraSetup:
		EraSetup.write(json.dumps(
			data___,
			indent=2,
			sort_keys=False
		))
		EraSetup.flush()
		EraSetup.close()

	for i in dirs[0]:
		if 'Era Setup #' in i:
			files.append(i)
			AddedFiles.append(i.replace(' ',''))

	write_ = '[EraSetupInformation]\n\t\t!Era Name!\t~\t%s\n\t\t!Action!\t~\t%s'
	for i in range(len(AddedFiles)):
		with open(AddedFiles[i],'wb') as AddedFile:
			AddedFile.write(write_ % (era[i-1] if len(era) > 1 else era[0], era_data[i-1] if len(era_data) > 1 else era_data[0]))
			AddedFile.flush()
			AddedFile.close()

	for i in files:
		os.remove(i);
	
	for i in range(len(dirs[0])):
		if 'EraSetup#' in dirs[0][i]:
			SaveFiles.append(dirs[0][i])
	for i in SaveFiles:
		if i in AddedFiles:
			pass
		if i not in AddedFiles:
			os.remove(i)

if len(listed_) != 0:
	for i in range(len(listed_)):
		data = open(listed_[i],'r').read()
		node_names.append(data)

	for i in range(len(node_names)):
		index = node_names[i].find(str(d))
		
		IdNumber.append(node_names[i][index])
		node_names[i] = node_names[i].replace('\n','')
		node_names[i] = node_names[i].replace(IdNumber[i],'')
		for i in range(len(IdNumber)):
			IdNumber[i] = int(IdNumber[i])

		ActionS = []

		for n in nums:
			if n in node_names[i]:
				ind = node_names[i].find(n)
				node_names[i] = node_names[i].replace(node_names[i][ind],'')
				IdNumber[i]+=int(n)
				if 12 in IdNumber:
					IIndex = IdNumber.index(10)
					IdNumber[IIndex+1]=11
		Action.append(node_names[i])
		node_names[i] = node_names[i].replace('Added Database Node ','')

		if node_names[i] == 'DefaultNodeSetup':
			node_names[i] = {'Default Node(NEEDED)':node_names[i]}
		if 'DefaultNodeSetup' in Action[i]:
			Action[i] = {'Default Node Added:':Action[i]}
		
		AllAddedFiles.append(listed_[i].replace(' ',''))
		d = d+1
	for x in range(len(data___['Era Types'])):
		ActionS.append(data___['Era Types'][x])
	
	data_ = {'Actions':ActionS,'NodeNames':node_names,'StorageData':DATA_,'NodeIds':IdNumber,'DataFiles':AllAddedFiles}

	
	for i in range(len(node_names)):
		DATA.append('[AddedDatabaseNode]\n\t\t!Node name!\t~\t%s\n\t\t!Node Id!\t~\t%s' % (node_names[i],IdNumber[i]))
	
	# If the user deletes the Database Nodes, this will update the files
	for i in range(len(dirs[0])):
		if 'NodeInformation#' in dirs[0][i]:
			FoundFiles.append(dirs[0][i])
	for i in FoundFiles:
		if i in AllAddedFiles:
			pass
		if not i in AllAddedFiles:
			os.remove(i)

	with open('NodeData.json','w') as NodeData:
		NodeData.write(json.dumps(
			data_,
			indent=2,
			sort_keys=False
		))
		NodeData.flush()
		NodeData.close()

	for i in range(len(listed_)):
		os.remove(listed_[i])
	
	for d in range(len(DATA)):

		with open(AllAddedFiles[d],'w') as w:
			w.write(DATA[d])
			w.close()
	for i in AllAddedFiles:
		DataOfFile = open(i,'r').read()
		if 'DefaultNodeSetup' in DataOfFile:
			new = '[DefaultNodeMsg]\n\t\tMESSAGE\t~\tREFER TO THE CreateDefaultNode FILE'
		
			with open(i,'w') as Update:
				Update.write(new)
				Update.flush()
				Update.close()
