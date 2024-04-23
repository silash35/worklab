const range = (min: number, max: number): number[] => {
  return Array.from({ length: max - min + 1 }, (_, i) => i + min);
};

// Create an array with all the possible combinations of chars with the given length
// Ex. length = 2, chars = ["a", "b", "c"] => ["aa", "ab", "ac", "ba", "bb", "bc", "ca", "cb", "cc"]
const combinations = (chars: string[], length: number) => {
  const temp: string[][] = Array(length - 1).fill(chars);
  const result: string[] = [];

  temp
    .reduce((acc, val) => {
      return acc.reduce((acc2: string[], char) => {
        return acc2.concat(val.map((innerChar) => char + innerChar));
      }, []);
    }, chars)
    .forEach((comb) => result.push(comb));

  return result;
};

export { combinations, range };
