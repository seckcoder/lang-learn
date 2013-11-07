from xlwt import Workbook

book = Workbook()
sheet = book.add_sheet('Sheet 1')
# row0 col0
sheet.write(0, 0, 'A1')
# row0 col1
sheet.write(0, 1, 'B1')
# get row1
row1 = sheet.row(1)
# row1 col0
row1.write(0, 'A2')
# row1 col1
row1.write(1, 'B2')
book.save('simple.xls')
