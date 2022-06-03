void substituiMinuscula (char str[]) {
    int i = 0;
    while ( str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
            i ++;
        }
    }
}
