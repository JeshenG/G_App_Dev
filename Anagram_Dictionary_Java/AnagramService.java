import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.HashMap;

public class AnagramService {
	/**
	 * Gets populated with data from the words list.
	 * List items may or not be anagrams
	 */
	Map<String,List<String>> word_map;   
	
	/**
	 * Gets populated with word-anagram pair lists.
	 * Each Key(Word) should have an ArrayList size thats greater than one.
	 */
	Map<String,List<String>> anagram_map; 
	
	/**
	 * Maximum word Length in the Dictionary.txt File
	 */
	int max_length;                      
	
	
		
	
	/**Method populates anagram_map.
	 * O(n) Complexity. 
	 * Iterates through original word_map, and stores only key-value pairs that have anagrams in them.
	 */
	public void populateAnagramMap() {
		anagram_map = new HashMap<String,List<String>>();
		
		for(String str : word_map.keySet()) {
			List<String> vals = word_map.get(str);
			if(vals.size() > 1) {
				anagram_map.put(str,vals); 
			}
		}
	}
	
	
		
	/**
	 * Function returns AnagramCounter object ArrayList.
	 * Counts the number of Anagrams for all word lengths less than max_length+1.  
	 * Makes use of Java 8 features 
	 * Complexity: Approximately O(n^2)
	 * @return ArrayList<AnagramCounter>
	 */
	public ArrayList<AnagramCounter> getAnagramCounterList(){
		int curr_length = 1;
		int curr_count  = 0;  
		ArrayList<AnagramCounter> return_list = new ArrayList<AnagramCounter>();
						
		while (curr_length < max_length + 1) {
			
			final int word_size = curr_length;
			
			//Now filter Map By key/word size (Java 8) Using streams 
			Map<String,List<String>> temp_map = anagram_map.entrySet()
					.stream()
					.filter(map -> map.getKey().length() == word_size)
					.collect(Collectors.toMap(map -> map.getKey(), map -> map.getValue()));
				
			//Now we have a temporary map that has list items for the current length
			//we want the list item count for all key-value pair list items
			for(String str : temp_map.keySet()) {
				curr_count = curr_count + temp_map.get(str).size();
			}
			
			//Create and append new AnagramCounter Object 
			AnagramCounter obj = new AnagramCounter(curr_length,curr_count);
			return_list.add(obj);
						
			//go to next word length
			curr_length++;
		}		
		return return_list;		
	}
	
	
 
    public List<AnagramCounter> compute(String dictionaryLocation) throws IOException {
        List<String> words = FileUtils.readLines(new File(dictionaryLocation));
               
        word_map = new HashMap<String,List<String>>();     
        max_length = words.get(0).length(); 
        
        for (String word : words) {
      
        	//get length of current word, and set max length if current word size is larger
        	int temp_length = word.length();
        	if(temp_length > max_length) {
        		max_length = temp_length;
        	}
        	
        	//Convert current word to char array and create a string that has characters in ascending order
        	//this string will be used as a key
            char [] chars = word.toCharArray();            
            Arrays.sort(chars);
            String str = new String(chars);
            
            //if sorted string/key exists in word_map, then add the current word to that specific key-list 
            if(word_map.containsKey(str)) {
            	(word_map.get(str)).add(word);
            }
            else {
            	//Else if the string/key does not exist in the word_map, then create a new ArrayList instance
            	//and add the current word to that new key-list
            	//finally we add the new key-value pair to the word_map 
            	List<String> word_lst = new ArrayList<String>();
            	word_lst.add(word);
            	word_map.put(str, word_lst);
            }      
        }
                      
        populateAnagramMap();        
        return getAnagramCounterList();        
    }
}

