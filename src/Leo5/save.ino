

void SaveData()
{
    writeInt(Micro);          // Int    2 bytes
    writeInt(xyz[1]);       // Int    2 bytes
    writeInt(RGB[0]);       // Int    2 bytes
    writeInt(RGB[1]);       // Int    2 bytes
    writeInt(RGB[2]);       // Int    2 bytes
    writeInt(Moteur[0]);       // Int    2 bytes
    writeInt(Moteur[1]);       // Int    2 bytes
    spi_transfer('\0');     // Char   1 byte
    spi_transfer('\n');     // Char   1 byte
     //                          =    16 bytes
  
  savingbyte += 16;
  
  
  if(savingbyte >= 528)
  {// Page full (528 bytes)
   savingbyte=0;

  
   
   
    
    
     if(flagSession==0)
        {// Enregistre le nombre de session
        
        Serial.print(F(" There are "));
        SavedSession = EEPROM.read(0x50);
         
        Serial.print(SavedSession);
        Serial.println(F(" sessions saved in memory."));
        SavedSession++;
        EEPROM.write(0x50,SavedSession);
        SavedSession--;
        
        if(SavedSession>=1) //Si ce n'est pas la première session, on charge la dernière page a avoir été ecrite
          {  
             savingpage = EEPROM_readLong(0x60+(SavedSession*4)-4); // Check what was the last page to be write
           
            Serial.print(F("Last page write was : "));
            Serial.println(savingpage);
            savingpage++; // puis on l'incrémente
          }
        else
          {  savingpage=0; // Sinon on écrit à 0
          Serial.println(F("Let s write to page 0"));
          }  


         flagSession=1;
        }
  
   
    Serial.print(F("new page "));
    Serial.println(savingpage);
    
    
    
    /* Transfer buffer 1 to 'page' page (with builtin erase) */
    
    dataflash.BufferToPage(1, (uint16_t)savingpage, 1);
    dataflash.BufferWrite(1, 0);
    
    // Save the number of stored page in eeprom
 
    EEPROM_writeLong(0x30, savingpage);
    EEPROM_writeLong((0x60+(SavedSession*4)), savingpage);// sauve dans le tableau des fichiers la dernière page écrite
    savingpage++;
    	
    if(savingpage>4000)
    {
      Serial.println("too long ");// ICI GERER MEMOIRE FULL
    }
  
  }




  
  }
