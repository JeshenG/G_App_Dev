import java.util.List;

public class Main {

    public static void main(String[] args) {
        try {
            String dictionaryLocation = "./resources/Dictionary.txt";

            long startTime = System.currentTimeMillis();
            List<AnagramCounter> anagramResults = new AnagramService().compute(dictionaryLocation);
            long endTime = System.currentTimeMillis();

            System.out.println();
            System.out.println("Anagram Results (completed in " + (endTime - startTime) + " ms):");
            System.out.println();

            for (AnagramCounter anagramCounter : anagramResults) {
                System.out.println("Words with the character length of " +  anagramCounter.getWordLength() +
                        " had " + anagramCounter.getCount() + " anagrams");
            }
        } catch (Exception e) {
            System.out.println("The following exception occurred:");
            System.out.println(e.getMessage());
        }
    }
}
