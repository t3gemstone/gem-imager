<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="tr_TR">
<context>
    <name>DfuThread</name>
    <message>
        <location filename="../dfuthread.cpp" line="49"/>
        <source>Failed to create temporary file for DFU image</source>
        <translation>DFU imaj için geçici dosya oluşturulamadı</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="59"/>
        <source>Failed to open temporary file for DFU image</source>
        <translation>DFU imaj için geçici dosya açılamadı</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="68"/>
        <source>Initializing DFU...</source>
        <translation>DFU başlatılıyor...</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="71"/>
        <source>DFU mode requires an image URL</source>
        <translation>DFU modu bir imaj URL'si gerektiriyor</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="75"/>
        <source>Downloading image...</source>
        <translation>İmaj indiriliyor...</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="80"/>
        <source>Extracting bootloader files from image...</source>
        <translation>İmaj'dan bootloader dosyaları çıkartılıyor...</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="83"/>
        <source>Sending bootloader files...</source>
        <translation>Bootloader dosyaları gönderiliyor...</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="86"/>
        <source>Waiting for device to enter DFU mode...</source>
        <translation>Cihazın DFU moduna girmesi bekleniyor...</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="89"/>
        <source>Sending image to device (this may take several minutes)...</source>
        <translation>İmaj cihaza gönderiliyor (bu birkaç dakika sürebilir)...</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="92"/>
        <source>Writing boot binaries to eMMC (do not power off)...</source>
        <translation>Boot binary dosyaları eMMC'ye yazılıyor (gücü kapatmayın)...</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="95"/>
        <source>System image sent successfully!</source>
        <translation>Sistem imajı başarıyla gönderildi!</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="111"/>
        <source>DFU failed (alt: %1): %2</source>
        <translation>DFU başarısız oldu (alt: %1): %2</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="127"/>
        <source>Sending %1...</source>
        <translation>%1 gönderiliyor...</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="130"/>
        <source>%1 sent</source>
        <translation>%1 gönderildi</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="133"/>
        <source>Waiting for device to reconnect...</source>
        <translation>Cihazın yeniden bağlanması bekleniyor...</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="150"/>
        <source>Failed to reopen image file: %1</source>
        <translation>İmaj dosyası yeniden açılamadı: %1</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="162"/>
        <source>Bootloader file not found in image: %1</source>
        <translation>İmaj'da bootloader dosyası bulunamadı: %1</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="173"/>
        <source>Failed to create temp file for %1</source>
        <translation>%1 için geçici dosya oluşturulamadı</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="178"/>
        <source>Failed to write temp file for %1</source>
        <translation>%1 için geçici dosya yazılamadı</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="187"/>
        <source>Error reading bootloader files from image: %1</source>
        <translation>İmaj'dan bootloader dosyaları okunurken hata: %1</translation>
    </message>
    <message>
        <location filename="../dfuthread.cpp" line="197"/>
        <source>Image not found: %1</source>
        <translation>İmaj bulunamadı: %1</translation>
    </message>
</context>
<context>
    <name>DownloadExtractThread</name>
    <message>
        <location filename="../downloadextractthread.cpp" line="196"/>
        <location filename="../downloadextractthread.cpp" line="385"/>
        <source>Error extracting archive: %1</source>
        <translation>Arşiv çıkarılırken hata oluştu: %1</translation>
    </message>
    <message>
        <location filename="../downloadextractthread.cpp" line="261"/>
        <source>Error mounting FAT32 partition</source>
        <translation>FAT32 bölümü bağlanırken hata oluştu</translation>
    </message>
    <message>
        <location filename="../downloadextractthread.cpp" line="281"/>
        <source>Operating system did not mount FAT32 partition</source>
        <translation>İşletim sistemi FAT32 bölümünü bağlamadı</translation>
    </message>
    <message>
        <location filename="../downloadextractthread.cpp" line="304"/>
        <source>Error changing to directory &apos;%1&apos;</source>
        <translation>Dizin değiştirirken hata oluştu &apos;%1&apos;</translation>
    </message>
    <message>
        <source>Error writing to storage</source>
        <translation type="vanished">Depolama birimine yazma hatası</translation>
    </message>
</context>
<context>
    <name>DownloadThread</name>
    <message>
        <location filename="../downloadthread.cpp" line="118"/>
        <source>unmounting drive</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="138"/>
        <source>opening drive</source>
        <translation>sürücü açılıyor</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="166"/>
        <source>Error running diskpart: %1</source>
        <translation>Diskpart çalıştırılırken hata oluştu: %1</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="187"/>
        <source>Error removing existing partitions</source>
        <translation>Mevcut bölümler kaldırılırken hata oluştu </translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="213"/>
        <source>Authentication cancelled</source>
        <translation>Kimlik doğrulama iptal edildi</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="216"/>
        <source>Error running authopen to gain access to disk device &apos;%1&apos;</source>
        <translation>&apos;%1&apos; disk aygıtına erişmek için authopen çalıştırılırken hata oluştu</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="217"/>
        <source>Please verify if &apos;Raspberry Pi Imager&apos; is allowed access to &apos;removable volumes&apos; in privacy settings (under &apos;files and folders&apos; or alternatively give it &apos;full disk access&apos;).</source>
        <translation>Lütfen &apos;Raspberry Pi Imager&apos;ın gizlilik ayarlarında (&apos;dosyalar ve klasörler&apos; altında veya alternatif olarak &apos;tam disk erişimi&apos;) &apos;çıkarılabilir birimlere erişim&apos; izin verilip verilmediğini doğrulayın.</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="239"/>
        <source>Cannot open storage device &apos;%1&apos;.</source>
        <translation>Depolama cihazı açılamıyor &apos;%1&apos;.</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="281"/>
        <source>discarding existing data on drive</source>
        <translation>sürücüdeki mevcut verileri sil</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="301"/>
        <source>zeroing out first and last MB of drive</source>
        <translation>sürücünün ilk ve son MB&apos;sini sıfırlama</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="307"/>
        <source>Write error while zero&apos;ing out MBR</source>
        <translation>MBR sıfırlanırken yazma hatası</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="319"/>
        <source>Write error while trying to zero out last part of card.&lt;br&gt;Card could be advertising wrong capacity (possible counterfeit).</source>
        <translation>Kartın son kısmını sıfırlamaya çalışırken yazma hatası. Kart yanlış kapasitenin tanımını yapıyor olabilir (olası sahte bölüm boyutu tanımı)</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="408"/>
        <source>starting download</source>
        <translation>indirmeye başlanıyor</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="468"/>
        <source>Error downloading: %1</source>
        <translation>İndirilirken hata oluştu: %1</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="665"/>
        <source>Access denied error while writing file to disk.</source>
        <translation>Dosyayı diske yazarken erişim reddedildi hatası</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="670"/>
        <source>Controlled Folder Access seems to be enabled. Please add both gem-imager.exe and fat32format.exe to the list of allowed apps and try again.</source>
        <translation>Kontrollü Klasör Erişimi etkin görünüyor. Lütfen izin verilen uygulamalar listesine hem gem-imager.exe&apos;yi hem de fat32format.exe&apos;yi ekleyin ve tekrar deneyin.</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="677"/>
        <source>Error writing file to disk</source>
        <translation>Dosyayı diske yazma hatası</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="699"/>
        <source>Download corrupt. Hash does not match</source>
        <translation>İndirme bozuk. Hash eşleşmiyor</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="711"/>
        <location filename="../downloadthread.cpp" line="763"/>
        <source>Error writing to storage (while flushing)</source>
        <translation>Depolama alanına yazma hatası (flushing sırasında)</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="718"/>
        <location filename="../downloadthread.cpp" line="770"/>
        <source>Error writing to storage (while fsync)</source>
        <translation>Depoya yazma hatası (fsync sırasında)</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="753"/>
        <source>Error writing first block (partition table)</source>
        <translation>İlk bloğu yazma hatası (partition table)</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="828"/>
        <source>Error reading from storage.&lt;br&gt;SD card may be broken.</source>
        <translation>Depolamadan okuma hatası.&lt;br&gt;SD kart arızalı olabilir.</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="847"/>
        <source>Verifying write failed. Contents of SD card is different from what was written to it.</source>
        <translation>Yazma doğrulanamadı. SD kartın içeriği, üzerine yazılandan farklı.</translation>
    </message>
    <message>
        <location filename="../downloadthread.cpp" line="900"/>
        <source>Customizing image</source>
        <translation>İmaj özelleştiriliyor</translation>
    </message>
    <message>
        <source>Error mounting FAT32 partition</source>
        <translation type="obsolete">FAT32 bölümü bağlanırken hata oluştu</translation>
    </message>
    <message>
        <source>Operating system did not mount FAT32 partition</source>
        <translation type="obsolete">İşletim sistemi FAT32 bölümünü bağlamadı</translation>
    </message>
</context>
<context>
    <name>DriveFormatThread</name>
    <message>
        <location filename="../driveformatthread.cpp" line="63"/>
        <location filename="../driveformatthread.cpp" line="124"/>
        <location filename="../driveformatthread.cpp" line="185"/>
        <source>Error partitioning: %1</source>
        <translation>Bölümleme hatası: %1</translation>
    </message>
    <message>
        <location filename="../driveformatthread.cpp" line="84"/>
        <source>Error starting fat32format</source>
        <translation>fat32format başlatılırken hata oluştu</translation>
    </message>
    <message>
        <location filename="../driveformatthread.cpp" line="94"/>
        <source>Error running fat32format: %1</source>
        <translation>fat32format çalıştırılırken hata oluştu: %1</translation>
    </message>
    <message>
        <location filename="../driveformatthread.cpp" line="104"/>
        <source>Error determining new drive letter</source>
        <translation>Yeni sürücü harfi belirlenirken hata oluştu</translation>
    </message>
    <message>
        <location filename="../driveformatthread.cpp" line="109"/>
        <source>Invalid device: %1</source>
        <translation>Geçersiz cihaz: %1</translation>
    </message>
    <message>
        <location filename="../driveformatthread.cpp" line="146"/>
        <source>Error formatting (through udisks2)</source>
        <translation>Hatalı biçimlendirme (udisks2 aracılığıyla)</translation>
    </message>
    <message>
        <location filename="../driveformatthread.cpp" line="174"/>
        <source>Error starting sfdisk</source>
        <translation>sfdisk başlatılırken hata oluştu</translation>
    </message>
    <message>
        <location filename="../driveformatthread.cpp" line="199"/>
        <source>Partitioning did not create expected FAT partition %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../driveformatthread.cpp" line="208"/>
        <source>Error starting mkfs.fat</source>
        <translation>mkfs.fat başlatılırken hata oluştu</translation>
    </message>
    <message>
        <location filename="../driveformatthread.cpp" line="218"/>
        <source>Error running mkfs.fat: %1</source>
        <translation>mkfs.fat çalıştırılırken hata oluştu: %1</translation>
    </message>
    <message>
        <location filename="../driveformatthread.cpp" line="225"/>
        <source>Formatting not implemented for this platform</source>
        <translation>Bu platform için biçimlendirme uygulanmadı</translation>
    </message>
</context>
<context>
    <name>ImageWriter</name>
    <message>
        <location filename="../imagewriter.cpp" line="253"/>
        <source>Storage capacity is not large enough.&lt;br&gt;Needs to be at least %1 GB.</source>
        <translation>Depolama kapasitesi yeterince büyük değil.&lt;br&gt;En az %1 GB olması gerekiyor</translation>
    </message>
    <message>
        <location filename="../imagewriter.cpp" line="259"/>
        <source>Input file is not a valid disk image.&lt;br&gt;File size %1 bytes is not a multiple of 512 bytes.</source>
        <translation>Giriş dosyası geçerli bir disk imaj'ı değil.&lt;br&gt;%1 bayt dosya boyutu 512 baytın katı değil.</translation>
    </message>
    <message>
        <location filename="../imagewriter.cpp" line="654"/>
        <source>Downloading and writing image</source>
        <translation>İmaj indiriliyor ve yazılıyor</translation>
    </message>
    <message>
        <location filename="../imagewriter.cpp" line="787"/>
        <source>Select image</source>
        <translation>İmaj seç</translation>
    </message>
    <message>
        <location filename="../imagewriter.cpp" line="962"/>
        <source>Error synchronizing time. Trying again in 3 seconds</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../imagewriter.cpp" line="974"/>
        <source>STP is enabled on your Ethernet switch. Getting IP will take long time.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../imagewriter.cpp" line="1185"/>
        <source>Would you like to prefill the wifi password from the system keychain?</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>LocalFileExtractThread</name>
    <message>
        <location filename="../localfileextractthread.cpp" line="34"/>
        <source>opening image file</source>
        <translation>imaj dosyası açılıyor</translation>
    </message>
    <message>
        <location filename="../localfileextractthread.cpp" line="39"/>
        <source>Error opening image file</source>
        <translation>İmaj dosyası açılırken hata oluştu</translation>
    </message>
</context>
<context>
    <name>MsgPopup</name>
    <message>
        <location filename="../MsgPopup.qml" line="98"/>
        <source>NO</source>
        <translation>HAYIR</translation>
    </message>
    <message>
        <location filename="../MsgPopup.qml" line="107"/>
        <source>YES</source>
        <translation>EVET</translation>
    </message>
    <message>
        <location filename="../MsgPopup.qml" line="116"/>
        <source>CONTINUE</source>
        <translation>DEVAM ET</translation>
    </message>
    <message>
        <location filename="../MsgPopup.qml" line="124"/>
        <source>QUIT</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>OptionsPopup</name>
    <message>
        <location filename="../OptionsPopup.qml" line="20"/>
        <source>OS Customization</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="62"/>
        <source>General</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="70"/>
        <source>Services</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="73"/>
        <source>Options</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="89"/>
        <source>Set hostname:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="112"/>
        <source>Set username and password</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="134"/>
        <source>Username:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="151"/>
        <location filename="../OptionsPopup.qml" line="220"/>
        <source>Password:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="187"/>
        <source>Configure wireless LAN</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="206"/>
        <source>SSID:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="239"/>
        <source>Show password</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="245"/>
        <source>Hidden SSID</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="251"/>
        <source>Wireless LAN country:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="262"/>
        <source>Set locale settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="272"/>
        <source>Time zone:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="282"/>
        <source>Keyboard layout:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="299"/>
        <source>Enable SSH</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="318"/>
        <source>Use password authentication</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="328"/>
        <source>Allow public-key authentication only</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="346"/>
        <source>Set authorized_keys for &apos;%1&apos;:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="358"/>
        <source>RUN SSH-KEYGEN</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="376"/>
        <source>Play sound when finished</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="380"/>
        <source>Eject media when finished</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="384"/>
        <source>Enable telemetry</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../OptionsPopup.qml" line="398"/>
        <source>SAVE</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../linux/linuxdrivelist.cpp" line="119"/>
        <source>Internal SD card reader</source>
        <translation>Dahili SD kart okuyucu</translation>
    </message>
</context>
<context>
    <name>UseSavedSettingsPopup</name>
    <message>
        <location filename="../UseSavedSettingsPopup.qml" line="77"/>
        <source>Use OS customization?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../UseSavedSettingsPopup.qml" line="92"/>
        <source>Would you like to apply OS customization settings?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../UseSavedSettingsPopup.qml" line="134"/>
        <source>NO</source>
        <translation>HAYIR</translation>
    </message>
    <message>
        <location filename="../UseSavedSettingsPopup.qml" line="115"/>
        <source>NO, CLEAR SETTINGS</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../UseSavedSettingsPopup.qml" line="125"/>
        <source>YES</source>
        <translation type="unfinished">EVET</translation>
    </message>
    <message>
        <location filename="../UseSavedSettingsPopup.qml" line="102"/>
        <source>EDIT SETTINGS</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>main</name>
    <message>
        <location filename="../main.qml" line="22"/>
        <source>Raspberry Pi Imager v%1</source>
        <translation>Raspberry Pi Imager v%1</translation>
    </message>
    <message>
        <location filename="../main.qml" line="119"/>
        <location filename="../main.qml" line="481"/>
        <source>Gemstone Board</source>
        <translation>Gemstone Board</translation>
    </message>
    <message>
        <location filename="../main.qml" line="131"/>
        <source>CHOOSE DEVICE</source>
        <translation>CİHAZ SEÇİN</translation>
    </message>
    <message>
        <location filename="../main.qml" line="143"/>
        <source>Select this button to choose your target Gemstone Board</source>
        <translation>Hedef Gemstone Board'u seçmek için bu düğmeye tıklayın</translation>
    </message>
    <message>
        <location filename="../main.qml" line="157"/>
        <location filename="../main.qml" line="584"/>
        <source>Operating System</source>
        <translation>İşletim sistemi</translation>
    </message>
    <message>
        <location filename="../main.qml" line="168"/>
        <location filename="../main.qml" line="1638"/>
        <source>CHOOSE OS</source>
        <translation>İŞLETİM SİSTEMİ SEÇİN</translation>
    </message>
    <message>
        <location filename="../main.qml" line="180"/>
        <source>Select this button to change the operating system</source>
        <translation>İşletim sistemini değiştirmek için bu düğmeyi seçin</translation>
    </message>
    <message>
        <location filename="../main.qml" line="194"/>
        <location filename="../main.qml" line="979"/>
        <source>Storage</source>
        <translation>Hedef</translation>
    </message>
    <message>
        <location filename="../main.qml" line="330"/>
        <source>Network not ready yet</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../main.qml" line="1007"/>
        <source>No storage devices found</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../main.qml" line="205"/>
        <location filename="../main.qml" line="1317"/>
        <source>CHOOSE STORAGE</source>
        <translation>HEDEFİ SEÇİN</translation>
    </message>
    <message>
        <source>WRITE</source>
        <translation type="vanished">YAZ</translation>
    </message>
    <message>
        <location filename="../main.qml" line="219"/>
        <source>Select this button to change the destination storage device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../main.qml" line="265"/>
        <source>CANCEL WRITE</source>
        <translation>YAZMAYI İPTAL ET</translation>
    </message>
    <message>
        <location filename="../main.qml" line="268"/>
        <location filename="../main.qml" line="1240"/>
        <source>Cancelling...</source>
        <translation>İptal ediliyor...</translation>
    </message>
    <message>
        <location filename="../main.qml" line="280"/>
        <source>CANCEL VERIFY</source>
        <translation>DOĞRULAMA İPTALİ</translation>
    </message>
    <message>
        <location filename="../main.qml" line="283"/>
        <location filename="../main.qml" line="1263"/>
        <location filename="../main.qml" line="1336"/>
        <source>Finalizing...</source>
        <translation>Bitiriliyor...</translation>
    </message>
    <message>
        <location filename="../main.qml" line="292"/>
        <source>Next</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../main.qml" line="298"/>
        <source>Select this button to start writing the image</source>
        <translation>İmaj yazmaya başlamak için bu düğmeyi seçin</translation>
    </message>
    <message>
        <location filename="../main.qml" line="320"/>
        <source>Using custom repository: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../main.qml" line="339"/>
        <source>Keyboard navigation: &lt;tab&gt; navigate to next button &lt;space&gt; press button/select item &lt;arrow up/down&gt; go up/down in lists</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../main.qml" line="360"/>
        <source>Language: </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../main.qml" line="383"/>
        <source>Keyboard: </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../main.qml" line="500"/>
        <source>[ All ]</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../main.qml" line="651"/>
        <source>Back</source>
        <translation>Geri</translation>
    </message>
    <message>
        <location filename="../main.qml" line="652"/>
        <source>Go back to main menu</source>
        <translation>Ana menüye dön</translation>
    </message>
    <message>
        <location filename="../main.qml" line="894"/>
        <source>Released: %1</source>
        <translation>Yayın: %1</translation>
    </message>
    <message>
        <location filename="../main.qml" line="904"/>
        <source>Cached on your computer</source>
        <translation>Bilgisayarınızda önbelleğe alındı
</translation>
    </message>
    <message>
        <location filename="../main.qml" line="906"/>
        <source>Local file</source>
        <translation>Yerel dosya</translation>
    </message>
    <message>
        <location filename="../main.qml" line="907"/>
        <source>Online - %1 GB download</source>
        <translation>Çevrimiçi - %1 GB indir</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1042"/>
        <location filename="../main.qml" line="1094"/>
        <location filename="../main.qml" line="1100"/>
        <source>Mounted as %1</source>
        <translation>%1 olarak bağlandı.</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1096"/>
        <source>[WRITE PROTECTED]</source>
        <translation>[YAZMA KORUMALI]</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1141"/>
        <source>Are you sure you want to quit?</source>
        <translation>Çıkmak istediğine emin misin?</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1142"/>
        <source>Raspberry Pi Imager is still busy.&lt;br&gt;Are you sure you want to quit?</source>
        <translation>Raspberry Pi Imager hala meşgul.&lt;br&gt;Çıkmak istediğinizden emin misiniz?</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1153"/>
        <source>Warning</source>
        <translation>Uyarı</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1162"/>
        <location filename="../main.qml" line="1444"/>
        <source>Preparing to write...</source>
        <translation>Yazmaya hazırlanıyor...</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1176"/>
        <source>All existing data on &apos;%1&apos; will be erased.&lt;br&gt;Are you sure you want to continue?</source>
        <translation>&apos;%1&apos; üzerindeki mevcut tüm veriler silinecek.&lt;br&gt;Devam etmek istediğinizden emin misiniz?</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1191"/>
        <source>Update available</source>
        <translation>Güncelleme bulunuyor</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1192"/>
        <source>There is a newer version of Imager available.&lt;br&gt;Would you like to visit the website to download it?</source>
        <translation>Imager'ın daha yeni bir sürümü var.&lt;br&gt;İndirmek için web sitesini ziyaret etmek ister misiniz?</translation>
    </message>
    <message>
        <source>Error downloading OS list from Internet</source>
        <translation type="vanished">İnternetten işletim sistemi listesi indirilirken hata oluştu</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1243"/>
        <source>Writing... %1%</source>
        <translation>Yazılıyor... %1%</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1266"/>
        <source>Verifying... %1%</source>
        <translation>Doğrulanıyor... %1%</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1273"/>
        <source>Preparing to write... (%1)</source>
        <translation>Yazmaya hazırlanıyor... (%1)</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1293"/>
        <source>Error</source>
        <translation>Hata</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1300"/>
        <source>Write Successful</source>
        <translation>Yazma Başarılı</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1301"/>
        <location filename="../imagewriter.cpp" line="596"/>
        <source>Erase</source>
        <translation>Sil</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1302"/>
        <source>&lt;b&gt;%1&lt;/b&gt; has been erased&lt;br&gt;&lt;br&gt;You can now remove the SD card from the reader</source>
        <translation>&lt;b&gt;%1&lt;/b&gt; silindi.&lt;br&gt;&lt;br&gt;Artık SD kartı okuyucudan çıkarabilirsiniz.</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1309"/>
        <source>&lt;b&gt;%1&lt;/b&gt; has been written to &lt;b&gt;%2&lt;/b&gt;&lt;br&gt;&lt;br&gt;You can now remove the SD card from the reader</source>
        <translation>&lt;b&gt;%1&lt;/b&gt;, &lt;b&gt;%2&lt;/b&gt; üzerine yazıldı.&lt;br&gt;&lt;br&gt;Artık SD kartı okuyucudan çıkarabilirsiniz.</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1463"/>
        <source>Error parsing os_list.json</source>
        <translation>os_list.json ayrıştırma hatası</translation>
    </message>
    <message>
        <location filename="../imagewriter.cpp" line="597"/>
        <source>Format card as FAT32</source>
        <translation>Kartı FAT32 olarak biçimlendir</translation>
    </message>
    <message>
        <location filename="../imagewriter.cpp" line="603"/>
        <source>Use custom</source>
        <translation>Özel imaj kullan</translation>
    </message>
    <message>
        <location filename="../imagewriter.cpp" line="604"/>
        <source>Select a custom .img from your computer</source>
        <translation>Bilgisayarınızdan özel bir .img seçin</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1712"/>
        <source>Connect an USB stick containing images first.&lt;br&gt;The images must be located in the root folder of the USB stick.</source>
        <translation>Önce imaj içeren bir USB bellek bağlayın.&lt;br&gt;İmaj'lar USB belleğin kök klasöründe bulunmalıdır.</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1728"/>
        <source>SD card is write protected.&lt;br&gt;Push the lock switch on the left side of the card upwards, and try again.</source>
        <translation>SD kart yazma korumalı.&lt;br&gt;Kartın sol tarafındaki kilit anahtarını yukarı itin ve tekrar deneyin.</translation>
    </message>
    <message>
        <source>Select this button to change the destination SD card</source>
        <translation type="vanished">Hedef SD kartı değiştirmek için bu düğmeyi seçin</translation>
    </message>
    <message>
        <source>&lt;b&gt;%1&lt;/b&gt; has been written to &lt;b&gt;%2&lt;/b&gt;</source>
        <translation type="vanished">&lt;b&gt;%1&lt;/b&gt; &lt;b&gt;%2&lt;/b&gt;&lt;br&gt;&lt;br&gt; üzerine yazıldı</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1213"/>
        <source>DFU Mode</source>
        <translation>DFU Modu</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1223"/>
        <source>Program the device via USB DFU (Device Firmware Update)</source>
        <translation>Cihazı USB DFU (Device Firmware Update) ile programla</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1392"/>
        <location filename="../main.qml" line="1399"/>
        <source>Boot Mode Switch</source>
        <translation>Boot Mode Switch</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1393"/>
        <source>Power off the card first. Then configure the boot mode switches for DFU Boot as shown in the image.</source>
        <translation>Önce kartı kapatın. Ardından boot mode anahtarlarını görseldeki gibi DFU konumuna getirin.</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1400"/>
        <source>Power off the card. Then set the boot mode switches to eMMC Boot as shown in the image. Upon restoring power, the system will boot automatically.</source>
        <translation>Kartı kapatın. Ardından anahtarları görseldeki gibi eMMC boot konumuna alın. Güç verildiğinde sistem otomatik olarak başlayacaktır.</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1410"/>
        <source>Gemstone Imager is still busy.&lt;br&gt;Are you sure you want to quit?</source>
        <translation>Gemstone Imager hâlâ meşgul.&lt;br&gt;Çıkmak istediğinizden emin misiniz?</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1486"/>
        <source>DFU Driver Not Found</source>
        <translation>DFU Sürücüsü Bulunamadı</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1487"/>
        <source>Windows DFU driver not found.&lt;br&gt;&lt;br&gt;Would you like to install the WinUSB driver?&lt;br&gt;(Administrator approval may be required)</source>
        <translation>Windows DFU sürücüsü bulunamadı.&lt;br&gt;&lt;br&gt;WinUSB sürücüsünü yüklemek istiyor musunuz?&lt;br&gt;(Yönetici onayı gerekebilir)</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1495"/>
        <source>Driver Installation Failed</source>
        <translation>Sürücü Kurulumu Başarısız</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1496"/>
        <source>Driver installation failed.&lt;br&gt;Please use &lt;a href=&apos;https://zadig.akeo.ie&apos;&gt;Zadig&lt;/a&gt;.</source>
        <translation>Sürücü kurulumu başarısız oldu.&lt;br&gt;Lütfen &lt;a href=&apos;https://zadig.akeo.ie&apos;&gt;Zadig&lt;/a&gt; uygulamasını kullanın.</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1438"/>
        <source>Starting DFU operation...</source>
        <translation>DFU işlemi başlatılıyor...</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1455"/>
        <source>Image will be sent to device via DFU.&lt;br&gt;Are you sure you want to continue?</source>
        <translation>İmaj, DFU aracılığıyla cihaza gönderilecek.&lt;br&gt;Devam etmek istediğinizden emin misiniz?</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1542"/>
        <source>Sending... %1%</source>
        <translation>Gönderiliyor... %1%</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1553"/>
        <source>Waiting for authentication to access USB device...</source>
        <translation>USB cihaza erişim için kimlik doğrulama bekleniyor...</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1619"/>
        <source>DFU programming completed successfully!&lt;br&gt;&lt;br&gt;The device has been programmed and should now boot automatically.</source>
        <translation>DFU programlama başarıyla tamamlandı!&lt;br&gt;&lt;br&gt;Cihaz programlandı, şimdi otomatik olarak boot edecektir.</translation>
    </message>
    <message>
        <location filename="../main.qml" line="1625"/>
        <source>&lt;b&gt;%1&lt;/b&gt; has been written to &lt;b&gt;%2&lt;/b&gt;&lt;br&gt;&lt;br&gt;The process is complete. You can connect to the board via the serial port.</source>
        <translation>&lt;b&gt;%1&lt;/b&gt;, &lt;b&gt;%2&lt;/b&gt; üzerine yazıldı.&lt;br&gt;&lt;br&gt;İşlem tamamlandı. Karta seri port üzerinden bağlanabilirsiniz.</translation>
    </message>
    <message>
        <location filename="../main.qml" line="2122"/>
        <source>Onboard emmc</source>
        <translation>Dahili eMMC</translation>
    </message>
</context>
</TS>
