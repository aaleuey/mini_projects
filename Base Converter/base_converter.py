def convert_fractional(num, base, precision=10):

    integer_part = int(num)
    frac_part = num - integer_part

    if base == 2:
        int_str = bin(integer_part)[2:]
    elif base == 8:
        int_str = oct(integer_part)[2:]
    elif base == 10:
        int_str = str(integer_part)
    elif base == 16:
        int_str = hex(integer_part)[2:].upper()

    frac_str = ""
    count = 0
    while frac_part > 0 and count < precision:
        frac_part *= base
        digit = int(frac_part)
        if base == 16 and digit >= 10:
            frac_str += chr(ord('A') + digit - 10)
        else:
            frac_str += str(digit)
        frac_part -= digit
        count += 1

    return int_str if frac_str == "" else f"{int_str}.{frac_str}"


def convert_number(base, value_str, precision=10):
    
    if '.' in value_str:
        integer_part, frac_part = value_str.split('.')
        num = int(integer_part, base) + int(frac_part, base) / (base ** len(frac_part))
    else:
        num = int(value_str, base)

    results = {
        "Bin": convert_fractional(num, 2, precision),
        "Oct": convert_fractional(num, 8, precision),
        "Dec": str(num),
        "Hex": convert_fractional(num, 16, precision),
    }
    return results


if __name__ == "__main__":
    print("\n\n=== Number Base Converter ===")
    print("\n     2: Binary\n     8: Octal\n    10: Decimal\n    16: Hexadecimal\n")

    choice = int(input("Select the base of the input value (2/8/10/16): "))
    value_str = input("Enter the number to convert: ")

    base_map = {2: 2, 8: 8, 10: 10, 16: 16}

    if choice in base_map:
        results = convert_number(base_map[choice], value_str, precision=10)
        print("\n\n=== Conversion Result ===\n")
        for key, val in results.items():
            print(f"{key}: {val}")
    else:
        print("Invalid choice. \nPlease select 2, 8, 10, or 16.")
