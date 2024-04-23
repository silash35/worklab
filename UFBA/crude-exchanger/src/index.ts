import { combinations, range } from "./generators";

function hasRepeatedDigits(text: string) {
  const digits = text.split("");
  const seen = new Set();
  for (const digit of digits) {
    if (seen.has(digit)) return true;
    seen.add(digit);
  }
  return false;
}

// Create an array with all the possible combinations (0 to 5555)
let array = range(0, 5555);
// let array = combinations(["0", "1", "2", "3", "4", "5"], 4);

// Filter the combinations that do not match the requirements of the problem
array = array.filter((item) => {
  const sItem = String(item);

  // The combination must not contain any of the numbers 6, 7, 8 or 9. Only the digits 0, 1, 2, 3, 4, 5 are allowed
  if (sItem.includes("6") || sItem.includes("7") || sItem.includes("8") || sItem.includes("9")) {
    return false;
  }

  // If the combination is not divisible by 5, it is not valid
  if (item % 5 !== 0) {
    return false;
  }

  // The combination must have exactly 4 digits
  if (sItem.length !== 4) {
    return false;
  }

  // The combination must not contain any repeated digits
  if (hasRepeatedDigits(sItem)) {
    return false;
  }

  return true;
});

console.log(array.length);
