if (month < 3) {
    month += 12;
    –year;
}
return dayray((int)(day + (month + 1) * 26/10 + year +
			year/4 + 6 * (year/100) + year/400)% 7);