import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Hashtable;
import java.util.stream.Stream;

class Test {
    public static void main(String[] args) {
        boolean binNB = true, checkStop = true;
        String posIn = "bop" + (binNB?"bin":"") + (checkStop?"stop":"") + ".obj";
        String negIn = "bon" + (binNB?"bin":"") + (checkStop?"stop":"") + ".obj";
        String vocab = "./aclImdb/imdb.vocab";
        String stopWordsFile = "./stopwords.txt";
        String posTest = "./aclImdb/test/pos";
        String negTest = "./aclImdb/test/neg";
        int noVocOri = 89527;
        int noVoc = 0;

        if(checkStop) {
            Hashtable<String, Integer> stopKeys = new Hashtable<>(174);
            try {
                Stream<String> stopWords = Files.lines(Paths.get(stopWordsFile));
                stopWords.forEach(word -> stopKeys.put(word, 1));
                Stream<String> initVocab = Files.lines(Paths.get(vocab));
                String[] tempVocab = initVocab.toArray(String[]::new);
                for (String word: tempVocab) {
                    if(!stopKeys.containsKey(word)) noVoc++;
                }
            }
            catch (IOException e) {
                System.out.println("IO exception occurred while reading... " + e);
                System.exit(1);
            }
        }
        else noVoc = noVocOri;

        double posPrecision, posRecall, posF1, negPrecision, negRecall, negF1;
        int tp = 0, tn = 0, fp = 0, fn = 0;
        File dir1 = new File(posTest), dir2 = new File(negTest);
        File[] posFiles = dir1.listFiles(), negFiles = dir2.listFiles();
        if(posFiles == null) {
            System.out.println("posFiles is null");
            System.exit(2);
        }
        if(negFiles == null) {
            System.out.println("posFiles is null");
            System.exit(2);
        }
        try {
            ObjectInputStream posStream = new ObjectInputStream(new FileInputStream(posIn));
            @SuppressWarnings("unchecked")
            Hashtable<String, Integer> posHash = (Hashtable<String, Integer>)posStream.readObject();
            ObjectInputStream negStream = new ObjectInputStream(new FileInputStream(negIn));
            @SuppressWarnings("unchecked")
            Hashtable<String, Integer> negHash = (Hashtable<String, Integer>)negStream.readObject();
            System.out.println("Testing Positive Examples....");
            int count = 1;
            for(File posFile: posFiles) {
                double posProb = 0.5, negProb = 0.5;
                try {
                    Stream<String> lines = Files.lines(posFile.toPath());
                    String[] wordLines = lines.toArray(String[]::new);
                    for(String wordLine : wordLines) {
                        String[] split = wordLine.split("\\s+");
                        for(String word: split) {
                            if(posHash.containsKey(word)) posProb *= (posHash.get(word) + 1)/(double)(posHash.get("$no") + noVoc);
                            else posProb *= 1/(double)(posHash.get("$no") + noVoc);
                            if(negHash.containsKey(word)) negProb *= (negHash.get(word) + 1)/(double)(negHash.get("$no") + noVoc);
                            else negProb *= 1/(double)(negHash.get("$no") + noVoc);
                        }
                    }
                }
                catch (IOException e) {
                    System.out.println("IO exception occurred while reading... " + e);
                    System.exit(1);
                }
                if(posProb >= negProb) tp++;
                else fn++;
                System.out.printf("\rPositive Example: %d | posProb: %.2f | negProb: %.2f | tp: %d | fn: %d", count, posProb, negProb, tp, fn);
                count++;
            }
            count = 1;
            System.out.println();
            System.out.println("Testing Negative Examples....");
            for(File negFile: negFiles) {
                double posProb = 0.5, negProb = 0.5;
                try {
                    Stream<String> lines = Files.lines(negFile.toPath());
                    String[] wordLines = lines.toArray(String[]::new);
                    for(String wordLine : wordLines) {
                        String[] split = wordLine.split("\\s+");
                        for(String word: split) {
                            if(posHash.containsKey(word)) posProb *= (posHash.get(word) + 1)/(double)(posHash.get("$no") + noVoc);
                            else posProb *= 1/(double)(posHash.get("$no") + noVoc);
                            if(negHash.containsKey(word)) negProb *= (negHash.get(word) + 1)/(double)(negHash.get("$no") + noVoc);
                            else negProb *= 1/(double)(negHash.get("$no") + noVoc);
                        }
                    }
                }
                catch (IOException e) {
                    System.out.println("IO exception occurred while reading... " + e);
                    System.exit(1);
                }
                if(posProb >= negProb) fp++;
                else tn++;
                System.out.printf("\rNegative Example: %d | posProb: %.2f | negProb: %.2f | fp: %d | tn: %d", count, posProb, negProb, fp, tn);
                count++;
            }
            posStream.close();
            negStream.close();
        }
        catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
            System.exit(3);
        }
        posPrecision = tp/(double)(tp+fp);
        posRecall = tp/(double)(tp+fn);
        posF1 = (2*posPrecision*posRecall)/(posPrecision+posRecall);
        negPrecision = fp/(double)(tp+fp);
        negRecall = fp/(double)(fp+tn);
        negF1 = (2*negPrecision*negRecall)/(negPrecision+negRecall);

        System.out.println();
        System.out.printf("Testing is done....\nStats....\nRead %s and %s\n", posIn, negIn);
        System.out.printf("Positive Testing Stats...\nPrecision: %f\nRecall: %f\nF1: %f\n", posPrecision, posRecall, posF1);
        System.out.printf("Negative Testing Stats...\nPrecision: %f\nRecall: %f\nF1: %f\n", negPrecision, negRecall, negF1);
    }
}
