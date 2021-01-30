use crate::prelude::*;

use std::collections::{HashMap, HashSet};

fn part_1(input: &str) -> usize {
    input.lines().fold(0, |sum, line| {
        let set: HashSet<&str> = line.split_whitespace().collect();
        if line.split_whitespace().count() != set.len() {
            sum
        } else {
            sum + 1
        }
    })
}

fn build_char_count_map(s: &str) -> HashMap<char, usize> {
    let mut map: HashMap<char, usize> = HashMap::new();

    for ch in s.chars() {
        let counter = map.entry(ch).or_insert(0);
        *counter += 1;
    }

    map
}

fn is_anagram(a: &str, b: &str) -> bool {
    if a.len() != b.len() {
        return false;
    } else {
        let a = build_char_count_map(a);
        let b = build_char_count_map(b);

        for (key, value) in &a {
            if let Some(v) = b.get(key) {
                if v != value {
                    return false;
                }
            } else {
                return false;
            }
        }

        return true;
    }
}

fn part_2(input: &str) -> usize {
    input.lines().fold(0, |sum, line| {
        let set: HashSet<&str> = line.split_whitespace().collect();
        if line.split_whitespace().count() != set.len() {
            sum
        } else {
            let set = set.iter().collect::<Vec<_>>(); // convert to vec to get random access [i]
            for i in 0..set.len() {
                for j in i + 1..set.len() {
                    if is_anagram(set[i], set[j]) {
                        return sum;
                    }
                }
            }
            sum + 1
        }
    })
}

// -----------------------------------------------------------------------------
// Run
// -----------------------------------------------------------------------------
pub(crate) fn run() -> Results {
    // -------------------------------------------------------------------------
    // Setup
    // -------------------------------------------------------------------------
    let start_setup = Instant::now();
    let input = std::fs::read_to_string("input/day04.txt").expect("Could not open day04.txt");
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
    output::print_day(4);
    output::print_part(1, "valid passphrases", &format!("{}", results.part_1));
    output::print_part(2, "valid passphrases", &format!("{}", results.part_2));
    output::print_timing(&results.times);
}

#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn part_1_example() {
        assert_eq!(part_1("aa bb cc dd ee"), 1);
        assert_eq!(part_1("aa bb cc dd aa"), 0);
        assert_eq!(part_1("aa bb cc dd aaa"), 1);
    }

    #[test]
    fn anagram_false() {
        assert!(!is_anagram("abcde", "fghij"));
    }

    #[test]
    fn anagram_true() {
        assert!(is_anagram("oiii", "ioii"));
    }

    #[test]
    fn anagram_different_length() {
        assert!(!is_anagram("xuz", "abcde"));
    }

    #[test]
    fn part_2_example() {
        assert_eq!(part_2("abcde fghij"), 1);
        assert_eq!(part_2("abcde xyz ecdab"), 0);
        assert_eq!(part_2("a ab abc abd abf abj"), 1);
        assert_eq!(part_2("iiii oiii ooii oooi oooo"), 1);
        assert_eq!(part_2("oiii ioii iioi iiio"), 0);
    }
}
