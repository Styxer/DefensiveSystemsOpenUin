Rainfull_mi = "45, 65, 70.4, 82.6, 20.1, 90.8, 76.1, 30.92, 46.8, 67.1, 79.9"

RAIN_THRESHOLD = 75

rainy_day_count = len([month for month in Rainfull_mi.split(",")  if float(month.strip()) > RAIN_THRESHOLD])

print(f'amount rainy days above {RAIN_THRESHOLD} mm of rain are {rainy_day_count}')