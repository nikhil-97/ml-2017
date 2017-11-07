import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Set;
import java.util.stream.Stream;

class Train {
    public static void main(String[] args) {
        boolean binNB = true, checkStop = true;
        String posOut = "bop" + (binNB?"bin":"") + (checkStop?"stop":"") + ".obj";
        String negOut = "bon" + (binNB?"bin":"") + (checkStop?"stop":"") + ".obj";
        String posTrainDir = "./aclImdb/train/pos";
        String negTrainDir = "./aclImdb/train/neg";
        String stopWordsFile = "./stopwords.txt";
        int noVocOri = 89527;
        Hashtable<String, Integer> posHash = new Hashtable<>(noVocOri);
        Hashtable<String, Integer> negHash = new Hashtable<>(noVocOri);
        Hashtable<String, Integer> stopKeys = new Hashtable<>(174);

        System.out.println(System.getProperty("user.dir"));
        try {
            Stream<String> stopWords = Files.lines(Paths.get(stopWordsFile));
            stopWords.forEach(word -> stopKeys.put(word, 1));
        }
        catch (IOException e) {
            System.out.println("IO exception occurred while reading... " + e);
            System.exit(1);
        }

        File dir1 = new File(posTrainDir), dir2 = new File(negTrainDir);
        File[] posFiles = dir1.listFiles(), negFiles = dir2.listFiles();
        if(posFiles == null) {
            System.out.println("posFiles is null");
            System.exit(2);
        }
        if(negFiles == null) {
            System.out.println("posFiles is null");
            System.exit(2);
        }

        int count = 1;
        for(File posFile: posFiles) {
            System.out.printf("\rCurrently training positive example %d", count);
            ArrayList<String> words = new ArrayList<>(2000);
            try {
                Stream<String> lines = Files.lines(posFile.toPath());
                String[] wordLines = lines.toArray(String[]::new);
                for(String wordLine : wordLines) {
                    String[] split = wordLine.split("\\s+");
                    for(String word: split) {
                        if(checkStop && stopKeys.containsKey(word)) {
                            continue;
                        }
                        words.add(word);
                    }
                }
            }
            catch (IOException e) {
                System.out.println("IO exception occurred while reading... " + e);
                System.exit(1);
            }
            if(!binNB) {
                for (String word: words) {
                    if(posHash.containsKey(word)) {
                        posHash.put(word, posHash.get(word) + 1);
                    }
                    else posHash.put(word, 1);
                    if(posHash.containsKey("$no")) {
                        posHash.put("$no", posHash.get("$no") + 1);
                    }
                    else posHash.put("$no", 1);
                }
            }
            else {
                Set<String> wordSet = new HashSet<>(words);
                for (String word: wordSet) {
                    if(posHash.containsKey(word)) {
                        posHash.put(word, posHash.get(word) + 1);
                    }
                    else posHash.put(word, 1);
                    if(posHash.containsKey("$no")) {
                        posHash.put("$no", posHash.get("$no") + 1);
                    }
                    else posHash.put("$no", 1);
                }
            }
            count++;
        }
        System.out.println();
        count = 1;
        for(File negFile: negFiles) {
            System.out.printf("\rCurrently training negative example %d", count);
            ArrayList<String> words = new ArrayList<>(2000);
            try {
                Stream<String> lines = Files.lines(negFile.toPath());
                String[] wordLines = lines.toArray(String[]::new);
                for(String wordLine : wordLines) {
                    String[] split = wordLine.split("\\s+");
                    for(String word: split) {
                        if(checkStop && stopKeys.containsKey(word)) {
                            continue;
                        }
                        words.add(word);
                    }
                }
            }
            catch (IOException e) {
                System.out.println("IO exception occurred while reading... " + e);
                System.exit(1);
            }
            if(!binNB) {
                for (String word: words) {
                    if(negHash.containsKey(word)) {
                        negHash.put(word, negHash.get(word) + 1);
                    }
                    else negHash.put(word, 1);
                    if(negHash.containsKey("$no")) {
                        negHash.put("$no", negHash.get("$no") + 1);
                    }
                    else negHash.put("$no", 1);
                }
            }
            else {
                Set<String> wordSet = new HashSet<>(words);
                for (String word: wordSet) {
                    if(negHash.containsKey(word)) {
                        negHash.put(word, negHash.get(word) + 1);
                    }
                    else negHash.put(word, 1);
                    if(negHash.containsKey("$no")) {
                        negHash.put("$no", negHash.get("$no") + 1);
                    }
                    else negHash.put("$no", 1);
                }
            }
            count++;
        }
        System.out.println();
        System.out.println("Training complete. Now storing to disk....");
        try {
            FileOutputStream fos = new FileOutputStream(posOut);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(posHash);
            oos.close();
            fos.close();
            System.out.printf("Serialized Hash table data is saved in %s\n", posOut);
        }
        catch(IOException ioe) {
            ioe.printStackTrace();
        }
        try {
            FileOutputStream fos = new FileOutputStream(negOut);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(negHash);
            oos.close();
            fos.close();
            System.out.printf("Serialized Hash table data is saved in %s\n", negOut);
        }
        catch(IOException ioe) {
            ioe.printStackTrace();
        }
    }
}
