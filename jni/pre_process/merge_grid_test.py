def main():
    with open('out1', 'w+') as output_data:
        for i in range(28):
            for j in range(28):
                output_data.write('0 ')
            output_data.write('\n')


if __name__ == '__main__':
    main()
