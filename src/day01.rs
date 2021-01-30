use crate::prelude::*;

// -----------------------------------------------------------------------------
// Part 1
// -----------------------------------------------------------------------------
// find the sum of all digits that match the next digit in the list.
// The list is circular, so the digit after the last digit is the
// first digit in the list.
fn part_1(input: &str) -> usize {
    let mut sum: usize = 0;

    let mut vec: Vec<usize> = Vec::with_capacity(input.len());

    for digit in input.chars() {
        if let Some(number) = digit.to_digit(10) {
            vec.push(number as usize);
        }
    }

    for (i, n) in vec.iter().enumerate() {
        if i + 1 == vec.len() {
            if *n == vec[0] {
                sum += n;
            }
        } else {
            if *n == vec[i + 1] {
                sum += n;
            }
        }
    }

    sum
}

// -----------------------------------------------------------------------------
// Part 2
// -----------------------------------------------------------------------------
fn part_2(input: &str) -> usize {
    let mut sum: usize = 0;

    let mut vec: Vec<usize> = Vec::with_capacity(2 * input.len());

    // not very efficient...
    for _ in 0..2 {
        for ch in input.chars() {
            if let Some(digit) = ch.to_digit(10) {
                vec.push(digit as usize);
            }
        }
    }

    let distance = vec.len() / 4;

    for (i, digit) in vec.iter().take(vec.len() / 2).enumerate() {
        if *digit == vec[i + distance] {
            sum += digit;
        }
    }

    sum
}

// -----------------------------------------------------------------------------
// Run
// -----------------------------------------------------------------------------
pub(crate) fn run() -> Results {
    // -------------------------------------------------------------------------
    // Setup
    // -------------------------------------------------------------------------
    let start_setup = Instant::now();
    let input = std::fs::read_to_string("input/day01.txt").expect("Could not open day01.txt");
    let time_setup = start_setup.elapsed();

    // -------------------------------------------------------------------------
    // Part 1
    // -------------------------------------------------------------------------
    let start_part_1 = Instant::now();
    let part_1 = part_1(&input);
    let time_part_1 = start_part_1.elapsed();

    // -------------------------------------------------------------------------
    // Part 2
    // -------------------------------------------------------------------------
    let start_part_2 = Instant::now();
    let part_2 = part_2(&input);
    let time_part_2 = start_part_2.elapsed();

    // -------------------------------------------------------------------------
    // Return
    // -------------------------------------------------------------------------
    Results::new(
        part_1 as i64,
        part_2 as i64,
        Timing::new(
            time_setup,
            time_part_1,
            time_part_2,
            time_setup + time_part_1 + time_part_2,
        ),
    )
}

// -----------------------------------------------------------------------------
// Report
// -----------------------------------------------------------------------------
pub(crate) fn report(results: &Results) {
    output::print_day(1);
    output::print_part(1, "sum", &format!("{}", results.part_1));
    output::print_part(2, "sum", &format!("{}", results.part_2));
    output::print_timing(&results.times);
}

// -----------------------------------------------------------------------------

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part_1_example() {
        assert_eq!(part_1("1122"), 1 + 2);
        assert_eq!(part_1("1111"), 1 + 1 + 1 + 1);
        assert_eq!(part_1("1234"), 0);
        assert_eq!(part_1("91212129"), 9);
    }

    #[test]
    fn part_2_example() {
        assert_eq!(part_2("1212"), 6);
        assert_eq!(part_2("1221"), 0);
        assert_eq!(part_2("123425"), 4);
        assert_eq!(part_2("123123"), 12);
        assert_eq!(part_2("12131415"), 4);
    }
}
