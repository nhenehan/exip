/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package org.acm.nhenehan.xsd2exip;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;
import org.junit.jupiter.api.Test;

/**
 *
 * @author Nathan Henehan <nhenehan@acm.org>
 */
public class MainTest {

    public MainTest() {
    }

    boolean compare(File file0, File file1) {

        try {

            byte[] bytes0 = Files.readAllBytes(Paths.get(file0.getAbsolutePath()));
            byte[] bytes1 = Files.readAllBytes(Paths.get(file1.getAbsolutePath()));

            String s0 = new String(Arrays.copyOfRange(bytes0, 0, 3), StandardCharsets.UTF_8);
            String s1 = new String(Arrays.copyOfRange(bytes1, 0, 3), StandardCharsets.UTF_8);

            if (bytes0.length != bytes1.length) {
                System.out.println("Byte Array Lenghts Differ: a0=" + bytes0.length + "a1=" + bytes1.length);
            }

            for (int i = 0; i < bytes0.length; ++i) {
                String bs0 = String.format("%8s", Integer.toBinaryString(bytes0[i] & 0xFF)).replace(' ', '0');
                String bs1 = String.format("%8s", Integer.toBinaryString(bytes1[i] & 0xFF)).replace(' ', '0');
                System.out.println(String.format("[%06d] %02x[%s] %02x[%s]", i, bytes0[i], bs0, bytes1[i], bs1));
                if (bytes0[i] != bytes1[i]) {
                    System.out.println("=> Stopping at first discrepancy <=");
                    return false;
                }
            }

            // since we already checked that the file sizes are equal 
            // if we're here we reached the end of both files without a mismatch
            return true;
        } catch (FileNotFoundException ex) {
            Logger.getLogger(MainTest.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(MainTest.class.getName()).log(Level.SEVERE, null, ex);
        }
        return false;
    }

    /**
     * Test of main method, of class Main.
     */
    @Test
    public void testMain() {
        System.out.println("main");
        File root = new File(".").getAbsoluteFile().getParentFile().getParentFile().getParentFile();

        System.out.println(root.getAbsolutePath());

        for (String filename : getFileNames()) {
            File exi0 = new File(root.getAbsoluteFile() + "/examples/simpleEncoding/"+filename+"-xsd.exi");
            File xsd1 = new File(root.getAbsoluteFile() + "/examples/simpleEncoding/"+filename+".xsd");
            File exi1 = new File(root.getAbsoluteFile() + "/examples/simpleEncoding/"+filename+"-xs2ex.exi");

            String[] args = {
                xsd1.getAbsolutePath(),
                exi1.getAbsolutePath()
            };

            Main.main(args);
            assertTrue(compare(exi0, exi1));
        }

//        File exi0 = new File(root.getAbsoluteFile() + "/examples/simpleEncoding/exipe-test-xsd.exi");
//        File xsd1 = new File(root.getAbsoluteFile() + "/examples/simpleEncoding/exipe-test.xsd");
//        File exi1 = new File("target/exipe-test-xsd-02.exi");
//
//        String[] args = {
//            xsd1.getAbsolutePath(),
//            exi1.getAbsolutePath()
//        };
//
// "${OUTPUT_PATH}" -schema=../examples/simpleEncoding/exipe-test-xs2ex.exi,../examples/simpleEncoding/exipe-test-types-xs2ex.exi,../examples/simpleEncoding/exipe-test-nested-xs2ex.exi outfile1.exi
// "${OUTPUT_PATH}" -schema=../examples/simpleEncoding/exipe-test-xsd.exi,../examples/simpleEncoding/exipe-test-types-xsd.exi,../examples/simpleEncoding/exipe-test-nested-xsd.exi outfile0.exi
//        Main.main(args);
//        assertTrue(compare(exi0, exi1));
    }

    private List<String> getFileNames() {
        List<String> flist = new ArrayList<>();
        flist.add("exipe-test");
        flist.add("exipe-test-types");
        flist.add("exipe-test-nested");
        return flist;
    }

}
