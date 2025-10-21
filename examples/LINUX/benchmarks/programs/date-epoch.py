from datetime import datetime

for i in range(10000):
    # Create a datetime object for the given epoch time: 10 Oct 2022 20:35:20
    date_epoch = datetime(2022, 10, 10, 20, 35, 20)
    # Convert epoch back to formatted date string
    date_string = date_epoch.strftime("%Y-%m-%d %H:%M:%S")

