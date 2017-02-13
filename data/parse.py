import csv

with open('pt-data2.csv') as f:
	with open('periodic-data.csv', 'w') as fw:
		reader = csv.reader(f, delimiter = ',')
		writer = csv.writer(fw, delimiter = ',')
		for row in reader:
			row[1] = row[1].replace(' ', '').upper()
			row[3] = row[3].replace(' ', '')
			row[3] = row[3].replace('[', '')
			row[3] = row[3].replace(']', '')
			if '(' in row[3]:
				row[3] = row[3][:-3]
			new_row = [row[1], row[3]]
			writer.writerow(new_row)
