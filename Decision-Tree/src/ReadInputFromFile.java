import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

class ReadInputFromFile {
    private String fileName;
    DataSet[] dataSetArr;

    ReadInputFromFile(String fileName){
        this.fileName = fileName;
    }
    void readStoreData(){
        BufferedReader br;

        dataSetArr = new DataSet[DataSet.noOfExamples];
        int length = 0;
        try {
            br = new BufferedReader(new FileReader(fileName));
            String currentLine;
            try {
                while ((currentLine = br.readLine()) != null){
                    dataSetArr[length] = new DataSet(currentLine);
                    length++;
                }
            }
            catch (IOException err){
                System.out.println("IO Exception Occurred!" + err);
            }
        }
        catch (FileNotFoundException err) {
            System.out.println("File is not found." + err);
        }
    }
}
