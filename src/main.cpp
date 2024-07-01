#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Text.h"
#include <windows.h>
OPENFILENAME ofn;
char szFile[100];

auto openFile(){
    static TCHAR g_BackupDir[MAX_PATH];
    GetCurrentDirectory(ARRAYSIZE(g_BackupDir), g_BackupDir);
    ZeroMemory( &ofn , sizeof( ofn));
    ofn.lStructSize = sizeof ( ofn );
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof( szFile );
    ofn.lpstrFilter = "Font\0 *.OTF;*.TTF";
    ofn.nFilterIndex =1;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir=nullptr;
    ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;

    GetOpenFileName( &ofn );
    SetCurrentDirectory(g_BackupDir);
    return ofn.lpstrFile;
}
//https://www.daniweb.com/programming/software-development/code/217307/a-simple-getopenfilename-example


int main() {
    srand(time(nullptr));
    double gameSpeed=0.4;
    int wordLength=0;
    int missInteger =0;
    int missScore =0;
    int chracterSize =25;
    int deafultChracterSize =25;
    std::string gameSpeedString="slow";
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game",sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    std::vector<Text> texts;
    std::vector<std::vector<std::string>> scoreVectorVector;
    std::vector<std::string> scoreVector;
    std::vector<std::string> words;
    std::vector<std::string> shortWords;
    std::vector<std::string> mediumWords;
    std::vector<std::string> longWords;
    sf::Font myFont;
    sf::Font myFontDefault;

    myFontDefault.loadFromFile("./assets/CoffeeFills.ttf");
    std::string myText;
    std::string fontLocationBackup;
    std::ifstream settingsStream("./assets/settings.txt");
    for (int i = 0; i < 4; ++i) {
        getline (settingsStream, myText);
        if(i==0){
            if(myText.empty()){
                chracterSize=30;
            }else{
                chracterSize=std::stoi(myText);
            }
        }
        if(i==1){
            if(myText.empty()){
                myFont.loadFromFile("./assets/ARIAL.TTF");
            }else{
                myFont.loadFromFile(myText);
                fontLocationBackup=myText;
            }

        }
        if(i==2){
            if(myText.empty()){
                gameSpeedString="slow";
            }else{
                gameSpeedString=myText;
            }

        }
        if(i==3){
            if(myText.empty()){
                wordLength=0;
            }else{
                wordLength=std::stoi(myText);
            }

        }
    }

    std::ifstream MyReadFile1("./assets/shortWords.txt");
    while (getline (MyReadFile1, myText)){
        shortWords.emplace_back(myText);
    }
    MyReadFile1.close();
    std::ifstream MyReadFile2("./assets/mediumWords.txt");
    while (getline (MyReadFile2, myText)){
        mediumWords.emplace_back(myText);
    }
    MyReadFile2.close();
    std::ifstream MyReadFile3("./assets/longWords.txt");
    while (getline (MyReadFile3, myText)){
        longWords.emplace_back(myText);
    }
    MyReadFile3.close();

    words=shortWords;
    bool whileBool =true;
    bool playGame =false;
    bool endScreen = false;
    bool settingBoolean =false;
    bool isSaved =false;
    sf::Clock timer;
    std::string fontLocation;
    //######################################
    //main screen
    //Play Button
    Text playText("Play", myFontDefault , 35, sf::Color::Magenta, sf::Text::Style::Bold, sf::Text::Style::Regular, 345, 210);
    sf::RectangleShape playButton(sf::Vector2f(150.f, 70.f));
    playButton.setPosition(310,200);
    playButton.setFillColor(sf::Color::Transparent);
    playButton.setOutlineThickness(10);
    playButton.setOutlineColor(sf::Color(255,254,12,90));
    //Settings Button
    Text settingsButtonText("Settings", myFontDefault , 35, sf::Color::Magenta, sf::Text::Style::Bold, sf::Text::Style::Regular, 317, 310);
    sf::RectangleShape settingsButton(sf::Vector2f(150.f, 70.f));
    settingsButton.setPosition(310, 300);
    settingsButton.setFillColor(sf::Color::Transparent);
    settingsButton.setOutlineThickness(10);
    settingsButton.setOutlineColor(sf::Color(255, 254, 12, 90));
    //Quit Button
    Text quitButtonText("Quit", myFontDefault , 35, sf::Color::Magenta, sf::Text::Style::Bold, sf::Text::Style::Regular, 345, 410);
    sf::RectangleShape quitButton(sf::Vector2f(150.f, 70.f));
    quitButton.setPosition(310, 400);
    quitButton.setFillColor(sf::Color::Transparent);
    quitButton.setOutlineThickness(10);
    quitButton.setOutlineColor(sf::Color(255, 254, 12, 90));
    Text gameTitle("Pink Carpet", myFontDefault , 75, sf::Color::Magenta, sf::Text::Style::Bold, sf::Text::Style::Regular, 180, 15);

    //######################################
    //settings
    sf::RectangleShape backButton(sf::Vector2f(35.f, 35.f));
    backButton.setPosition(25,25);
    backButton.setFillColor(sf::Color::Transparent);
    backButton.setOutlineThickness(5);
    backButton.setOutlineColor(sf::Color(255,254,12,90));
    sf::RectangleShape backButtonLine1(sf::Vector2f(2.f, 17.f));
    backButtonLine1.setPosition(48,31);
    backButtonLine1.rotate(45);
    sf::RectangleShape backButtonLine2(sf::Vector2f(2.f, 15.f));
    backButtonLine2.setPosition(36,43);
    backButtonLine2.rotate(-45);
    //font
    Text setFontText("setFont", myFont ,45, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 520, 40);
    //######################################
    sf::RectangleShape Font1(sf::Vector2f(200.f, 100.f));
    Font1.setPosition(500,20);
    Font1.setFillColor(sf::Color::Transparent);
    Font1.setOutlineThickness(5);
    Font1.setOutlineColor(sf::Color(255,254,12,90));
    //######################################
    Text shortWordsText("Short", myFont ,25, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 95, 23);
    //######################################
    sf::RectangleShape shortWordsButton(sf::Vector2f(100.f, 40.f));
    shortWordsButton.setPosition(80,20);
    shortWordsButton.setFillColor(sf::Color::Transparent);
    shortWordsButton.setOutlineThickness(5);
    shortWordsButton.setOutlineColor(sf::Color(255,254,12,90));
    //######################################
    Text mediumWordsText("Medium", myFont ,20, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 210, 27);
    //######################################
    sf::RectangleShape mediumWordsButton(sf::Vector2f(100.f, 40.f));
    mediumWordsButton.setPosition(200,20);
    mediumWordsButton.setFillColor(sf::Color::Transparent);
    mediumWordsButton.setOutlineThickness(5);
    mediumWordsButton.setOutlineColor(sf::Color(255,254,12,90));
    //######################################
    //######################################
    Text longWordsText("Long", myFont ,25, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 340, 23);
    //######################################
    sf::RectangleShape longWordsButton(sf::Vector2f(100.f, 40.f));
    longWordsButton.setPosition(320,20);
    longWordsButton.setFillColor(sf::Color::Transparent);
    longWordsButton.setOutlineThickness(5);
    longWordsButton.setOutlineColor(sf::Color(255,254,12,90));
    //######################################
    sf::RectangleShape sliderStick(sf::Vector2f(300.f, 3.f));
    sliderStick.setPosition(200,300);
    //######################################
    sf::CircleShape sliderCircle(10.f);
    sliderCircle.setOrigin(10.f,10.f);
    sliderCircle.setFillColor(sf::Color(255, 255, 255));
    sliderCircle.setPosition(200,300);
    //######################################
    Text slowText("Slow", myFont ,25, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 100, 83);
    //######################################
    sf::RectangleShape slowButton(sf::Vector2f(100.f, 40.f));
    slowButton.setPosition(80,80);
    slowButton.setFillColor(sf::Color::Transparent);
    slowButton.setOutlineThickness(5);
    slowButton.setOutlineColor(sf::Color(255,254,12,90));
    //######################################
    Text midText("Mid", myFont ,20, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 230, 87);
    //######################################
    sf::RectangleShape midButton(sf::Vector2f(100.f, 40.f));
    midButton.setPosition(200,80);
    midButton.setFillColor(sf::Color::Transparent);
    midButton.setOutlineThickness(5);
    midButton.setOutlineColor(sf::Color(255,254,12,90));
    //######################################
    //######################################
    Text fastText("Fast", myFont ,25, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 340, 83);
    //######################################
    sf::RectangleShape fastButton(sf::Vector2f(100.f, 40.f));
    fastButton.setPosition(320,80);
    fastButton.setFillColor(sf::Color::Transparent);
    fastButton.setOutlineThickness(5);
    fastButton.setOutlineColor(sf::Color(255,254,12,90));
    //######################################
    Text sliderText("Text Size", myFont ,chracterSize, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 340, 350);
    sliderText.text.setOrigin(sliderText.text.getLocalBounds().width/2,sliderText.text.getLocalBounds().height/2);
    //######################################

    //end game
    Text endGameText("Game Over", myFontDefault , 50, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 100, 25);
    Text mainMenuButtonText("Main Menu", myFontDefault , 50, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 450, 450);
    Text saveScoreButtonText("Save Score", myFontDefault , 50, sf::Color::Green, sf::Text::Style::Bold, sf::Text::Style::Regular, 65, 450);
    sf::RectangleShape mainMenuButton(sf::Vector2f(280.f, 100.f));
    mainMenuButton.setPosition( 440,435);
    mainMenuButton.setFillColor(sf::Color::Transparent);
    mainMenuButton.setOutlineThickness(3);
    mainMenuButton.setOutlineColor(sf::Color(255,254,12,50));
    sf::RectangleShape saveScoreButton(sf::Vector2f(280.f, 100.f));
    saveScoreButton.setPosition(60,435);
    saveScoreButton.setFillColor(sf::Color::Transparent);
    saveScoreButton.setOutlineThickness(3);
    saveScoreButton.setOutlineColor(sf::Color(255,254,12,50));



    //######################################
    //game
    sf::RectangleShape line(sf::Vector2f(780.f, 130.f));
    line.setPosition(10,460);
    line.setFillColor(sf::Color::Transparent);
    line.setOutlineThickness(10);
    line.setOutlineColor(sf::Color(255,254,12,90));
    Text myKelime("", myFontDefault , chracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 330, 470);
    myKelime.text.setOrigin(myKelime.text.getLocalBounds().width/2,myKelime.text.getLocalBounds().height/2);
    Text writedWordsNumber("0", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 650, 490);
    Text writedWords("Correct Written words", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 540, 460);
    Text wrongWritedWords("Wrong Written words", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 540, 520);
    Text wrongWritedWordsNumber("0", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 650, 550);
    Text scoreText("Score", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 15, 460);
    Text scoreNumber("0", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 39, 490);
    Text WPM("WPM", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 15, 520);
    Text WPM_Number("0", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 39, 550);
    Text missedWords("Missed words", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 110, 460);
    Text missedWordsNumber("0", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 180, 490);
    Text timeWords("Seconds", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 330, 510);
    Text timeNumber("0", myFontDefault , deafultChracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, 370, 540);
    //######################################

    if(gameSpeedString=="slow"){
        gameSpeed=0.4;
        slowText.text.setFillColor(sf::Color::Yellow);
    }else if (gameSpeedString=="mid"){
        gameSpeed=0.8;
        midText.text.setFillColor(sf::Color::Yellow);
    }else if (gameSpeedString=="fast"){
        gameSpeed=1.3;
        fastText.text.setFillColor(sf::Color::Yellow);
    }
    if(wordLength==0){
        shortWordsText.text.setFillColor(sf::Color::Yellow);
        words=shortWords;
    }else if (wordLength==1){
        mediumWordsText.text.setFillColor(sf::Color::Yellow);
        words=mediumWords;

    }else if (wordLength==2){
        longWordsText.text.setFillColor(sf::Color::Yellow);
        words=longWords;
    }

    while (window.isOpen()){

        if (missScore==8){
            playGame=false;
            endScreen=true;
            isSaved=false;
        }

        if (texts.size()<8){
            int x =(std::rand()%300+50)*-1;
            int y =std::rand()%350;
            while (true){
                bool changed = false;
                for (int i = 0; i < texts.size(); ++i) {
                    if (std::abs(y-texts[i].text.getPosition().y)<30){
                        y =std::rand()%350;
                        changed = true;
                    }
                }
                if (!changed){
                    break;
                }
            }
            std::string nextWord =words[std::rand()%words.size()];
            texts.emplace_back(nextWord, myFont , chracterSize, sf::Color::Green, sf::Text::Style::Italic, sf::Text::Style::Regular, x,y);
            for (int i = 0; i < texts.size(); ++i) {
                if (nextWord==texts[i].text.getString()){
                    texts[i].text.setString(words[std::rand()%words.size()]);
                }
            }
        }

        timeNumber.text.setString(std::to_string((int)timer.getElapsedTime().asSeconds()));
        sf::Event event{};
        if (!playGame && !settingBoolean&& !endScreen){




            std::ifstream scoreReader("./assets/score.txt");
            std::string scoreReaderText;
            while (whileBool){
                for (int i = 0; i < 5; ++i) {

                    if (!getline(scoreReader, scoreReaderText)) {
                        whileBool=false;
                    }

                    scoreVector.emplace_back(scoreReaderText);
                }
            }
            scoreReader.close();


            if (sf::Mouse::getPosition(window).x>=300&&sf::Mouse::getPosition(window).x<=470&&sf::Mouse::getPosition(window).y>=190&&sf::Mouse::getPosition(window).y<=280){
                playButton.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                playButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=300&&sf::Mouse::getPosition(window).x<=470&&sf::Mouse::getPosition(window).y>=290&&sf::Mouse::getPosition(window).y<=380){
                settingsButton.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                settingsButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=300&&sf::Mouse::getPosition(window).x<=470&&sf::Mouse::getPosition(window).y>=390&&sf::Mouse::getPosition(window).y<=480){
                quitButton.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                quitButton.setOutlineColor(sf::Color(255,254,12,90));
            }


            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if (sf::Mouse::getPosition(window).x>=300&&sf::Mouse::getPosition(window).x<=470&&sf::Mouse::getPosition(window).y>=190&&sf::Mouse::getPosition(window).y<=280){
                        playButton.setOutlineColor(sf::Color(255,254,12,90));
                        writedWords.text.setPosition(540,460);
                        writedWordsNumber.text.setPosition(650,490);
                        wrongWritedWords.text.setPosition(540,520);
                        wrongWritedWordsNumber.text.setPosition(650,550);
                        scoreText.text.setPosition(15,460);
                        scoreNumber.text.setPosition(39,490);
                        WPM.text.setPosition(15,520);
                        WPM_Number.text.setPosition(39,550);
                        missedWords.text.setPosition(110,460);
                        missedWordsNumber.text.setPosition(180,490);
                        texts.clear();
                        timer.restart();
                        myKelime.text.setString("");

                        playGame = true;
                    }

                    if (sf::Mouse::getPosition(window).x>=300&&sf::Mouse::getPosition(window).x<=470&&sf::Mouse::getPosition(window).y>=290&&sf::Mouse::getPosition(window).y<=380){
                        settingsButton.setOutlineColor(sf::Color(255,254,12,90));
                        settingBoolean=true;
                    }
                    if (sf::Mouse::getPosition(window).x>=300&&sf::Mouse::getPosition(window).x<=470&&sf::Mouse::getPosition(window).y>=390&&sf::Mouse::getPosition(window).y<=480){
                        quitButton.setOutlineColor(sf::Color(255,254,12,90));
                        window.close();
                    }
                }

            }

            window.clear();
            window.draw(playButton);
            window.draw(playText.text);
            window.draw(settingsButton);
            window.draw(settingsButtonText.text);
            window.draw(quitButton);
            window.draw(quitButtonText.text);
            window.draw(gameTitle.text);
        }



        //settings
        if (settingBoolean){
            if (sf::Mouse::getPosition(window).x>=20&&sf::Mouse::getPosition(window).x<=65&&sf::Mouse::getPosition(window).y>=20&&sf::Mouse::getPosition(window).y<=65){
                backButton.setOutlineColor(sf::Color(255,254,12,255));


            }else{
                backButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=20&&sf::Mouse::getPosition(window).x<=65&&sf::Mouse::getPosition(window).y>=20&&sf::Mouse::getPosition(window).y<=65){
                backButton.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                backButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=495&&sf::Mouse::getPosition(window).x<=705&&sf::Mouse::getPosition(window).y>=15&&sf::Mouse::getPosition(window).y<=125){
                Font1.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                Font1.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=75&&sf::Mouse::getPosition(window).x<=183&&sf::Mouse::getPosition(window).y>=15&&sf::Mouse::getPosition(window).y<=65){
                shortWordsButton.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                shortWordsButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=195&&sf::Mouse::getPosition(window).x<=305&&sf::Mouse::getPosition(window).y>=15&&sf::Mouse::getPosition(window).y<=65){
                mediumWordsButton.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                mediumWordsButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=315&&sf::Mouse::getPosition(window).x<=425&&sf::Mouse::getPosition(window).y>=15&&sf::Mouse::getPosition(window).y<=65){
                longWordsButton.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                longWordsButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=75&&sf::Mouse::getPosition(window).x<=183&&sf::Mouse::getPosition(window).y>=75&&sf::Mouse::getPosition(window).y<=125){
                slowButton.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                slowButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=195&&sf::Mouse::getPosition(window).x<=305&&sf::Mouse::getPosition(window).y>=75&&sf::Mouse::getPosition(window).y<=125){
                midButton.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                midButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=315&&sf::Mouse::getPosition(window).x<=425&&sf::Mouse::getPosition(window).y>=75&&sf::Mouse::getPosition(window).y<=125){
                fastButton.setOutlineColor(sf::Color(255,254,12,255));
            }else{
                fastButton.setOutlineColor(sf::Color(255,254,12,90));
            }


            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();


                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    //std::cout<<sf::Mouse::getPosition(window).x<<" "<<sf::Mouse::getPosition(window).y<<"\n";

                    if (sf::Mouse::getPosition(window).x>=20&&sf::Mouse::getPosition(window).x<=65&&sf::Mouse::getPosition(window).y>=20&&sf::Mouse::getPosition(window).y<=65){
                        backButton.setOutlineColor(sf::Color(255,254,12,255));

                        std::ofstream settingsFile;

                        settingsFile.open("./assets/settings.txt");
                        settingsFile << chracterSize <<std::endl;
                        if(!fontLocation.empty()){
                            settingsFile << fontLocation <<std::endl;
                        }else{
                            if (fontLocationBackup.empty()){
                                settingsFile << "./assets/ARIAL.TTF" <<std::endl;
                            }else
                            settingsFile << fontLocationBackup <<std::endl;
                        }
                        settingsFile << gameSpeedString <<std::endl;
                        settingsFile << wordLength <<std::endl;

                        settingsFile.close();
                        settingBoolean = false;
                    }
                    if (sf::Mouse::getPosition(window).x>=495&&sf::Mouse::getPosition(window).x<=705&&sf::Mouse::getPosition(window).y>=15&&sf::Mouse::getPosition(window).y<=125){
                        Font1.setOutlineColor(sf::Color(255,254,12,255));
                        fontLocation=openFile();
                        if(!fontLocation.empty())
                            myFont.loadFromFile(fontLocation);
                    }
                    if (sf::Mouse::getPosition(window).x>=75&&sf::Mouse::getPosition(window).x<=183&&sf::Mouse::getPosition(window).y>=15&&sf::Mouse::getPosition(window).y<=65){
                        shortWordsButton.setOutlineColor(sf::Color(255,254,12,50));
                        shortWordsText.text.setFillColor(sf::Color::Yellow);
                        mediumWordsText.text.setFillColor(sf::Color::Green);
                        longWordsText.text.setFillColor(sf::Color::Green);
                        words=shortWords;
                        wordLength=0;
                    }
                    if (sf::Mouse::getPosition(window).x>=195&&sf::Mouse::getPosition(window).x<=305&&sf::Mouse::getPosition(window).y>=15&&sf::Mouse::getPosition(window).y<=65){
                        mediumWordsButton.setOutlineColor(sf::Color(255,254,12,50));
                        shortWordsText.text.setFillColor(sf::Color::Green);
                        mediumWordsText.text.setFillColor(sf::Color::Yellow);
                        longWordsText.text.setFillColor(sf::Color::Green);
                        words=mediumWords;
                        wordLength=1;
                    }
                    if (sf::Mouse::getPosition(window).x>=315&&sf::Mouse::getPosition(window).x<=425&&sf::Mouse::getPosition(window).y>=15&&sf::Mouse::getPosition(window).y<=65){
                        longWordsButton.setOutlineColor(sf::Color(255,254,12,50));
                        shortWordsText.text.setFillColor(sf::Color::Green);
                        mediumWordsText.text.setFillColor(sf::Color::Green);
                        longWordsText.text.setFillColor(sf::Color::Yellow);
                        words=longWords;
                        wordLength=2;
                    }
                    if (sf::Mouse::getPosition(window).x>=75&&sf::Mouse::getPosition(window).x<=183&&sf::Mouse::getPosition(window).y>=75&&sf::Mouse::getPosition(window).y<=125){
                        slowButton.setOutlineColor(sf::Color(255,254,12,50));
                        slowText.text.setFillColor(sf::Color::Yellow);
                        midText.text.setFillColor(sf::Color::Green);
                        fastText.text.setFillColor(sf::Color::Green);
                        gameSpeedString="slow";
                        gameSpeed=0.4;
                    }
                    if (sf::Mouse::getPosition(window).x>=195&&sf::Mouse::getPosition(window).x<=305&&sf::Mouse::getPosition(window).y>=75&&sf::Mouse::getPosition(window).y<=125){
                        midButton.setOutlineColor(sf::Color(255,254,12,50));
                        slowText.text.setFillColor(sf::Color::Green);
                        midText.text.setFillColor(sf::Color::Yellow);
                        fastText.text.setFillColor(sf::Color::Green);
                        gameSpeedString="mid";
                        gameSpeed=0.8;
                    }
                    if (sf::Mouse::getPosition(window).x>=315&&sf::Mouse::getPosition(window).x<=425&&sf::Mouse::getPosition(window).y>=75&&sf::Mouse::getPosition(window).y<=125){
                        fastButton.setOutlineColor(sf::Color(255,254,12,50));
                        slowText.text.setFillColor(sf::Color::Green);
                        midText.text.setFillColor(sf::Color::Green);
                        fastText.text.setFillColor(sf::Color::Yellow);
                        gameSpeedString="fast";
                        gameSpeed=1.3;
                    }


                    double x = sf::Mouse::getPosition(window).x-sliderCircle.getPosition().x;
                    double y = sf::Mouse::getPosition(window).y-sliderCircle.getPosition().y;
                    double mouseDistance = sqrt(x*x+y*y);
                    bool slider = false;
                    if (mouseDistance<10){
                        if(sliderCircle.getPosition().x>=200&& sliderCircle.getPosition().x<=500)
                        slider=true;
                        while (slider){
                                sliderCircle.setPosition(sf::Mouse::getPosition(window).x,sliderCircle.getPosition().y);
                            if(sliderCircle.getPosition().x<200)
                                sliderCircle.setPosition(201,sliderCircle.getPosition().y);
                            if (sliderCircle.getPosition().x>500)
                                sliderCircle.setPosition(499,sliderCircle.getPosition().y);

                            auto ratio = static_cast<float>(sliderCircle.getPosition().x - 200) / (500 - 200);

                            chracterSize = ratio * (40 - 20) + 20;
                            sliderText.text.setCharacterSize(chracterSize);
                            window.clear();
                            window.draw(backButton);
                            window.draw(backButtonLine1);
                            window.draw(backButtonLine2);
                            window.draw(Font1);
                            window.draw(sliderStick);
                            window.draw(sliderCircle);
                            window.draw(sliderText.text);
                            window.draw(setFontText.text);
                            window.draw(shortWordsText.text);
                            window.draw(mediumWordsText.text);
                            window.draw(longWordsText.text);
                            window.draw(shortWordsButton);
                            window.draw(mediumWordsButton);
                            window.draw(longWordsButton);
                            window.draw(slowButton);
                            window.draw(midButton);
                            window.draw(fastButton);
                            window.draw(slowText.text);
                            window.draw(midText.text);
                            window.draw(fastText.text);

                            window.display();
                            if  (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                                slider=false;

                        }



                    }



                }
            }
            window.clear();
            window.draw(backButton);
            window.draw(backButtonLine1);
            window.draw(backButtonLine2);
            window.draw(Font1);
            window.draw(sliderStick);
            window.draw(sliderCircle);
            window.draw(sliderText.text);
            window.draw(setFontText.text);
            window.draw(shortWordsText.text);
            window.draw(mediumWordsText.text);
            window.draw(longWordsText.text);
            window.draw(shortWordsButton);
            window.draw(mediumWordsButton);
            window.draw(longWordsButton);
            window.draw(slowButton);
            window.draw(midButton);
            window.draw(fastButton);
            window.draw(slowText.text);
            window.draw(midText.text);
            window.draw(fastText.text);


        }
        //endgamescreen
        if(endScreen){
            if (sf::Mouse::getPosition(window).x>=56&&sf::Mouse::getPosition(window).x<=342&&sf::Mouse::getPosition(window).y>=430&&sf::Mouse::getPosition(window).y<=537){
                saveScoreButton.setOutlineColor(sf::Color(255,254,12,255));


            }else{
                saveScoreButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            if (sf::Mouse::getPosition(window).x>=437&&sf::Mouse::getPosition(window).x<=723&&sf::Mouse::getPosition(window).y>=430&&sf::Mouse::getPosition(window).y<=537){
                mainMenuButton.setOutlineColor(sf::Color(255,254,12,255));


            }else{
                mainMenuButton.setOutlineColor(sf::Color(255,254,12,90));
            }
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if (sf::Mouse::getPosition(window).x>=56&&sf::Mouse::getPosition(window).x<=342&&sf::Mouse::getPosition(window).y>=430&&sf::Mouse::getPosition(window).y<=537){
                        saveScoreButton.setOutlineColor(sf::Color(255,254,12,255));
                        if  (!isSaved){
                            std::ofstream scoreFile;
                            scoreFile.open ("./assets/score.txt", std::ofstream::app);
                            scoreFile << (std::string)writedWordsNumber.text.getString() <<std::endl;
                            scoreFile << (std::string)wrongWritedWordsNumber.text.getString() <<std::endl;
                            scoreFile << (std::string)scoreNumber.text.getString() <<std::endl;
                            scoreFile << (std::string)WPM_Number.text.getString() <<std::endl;
                            scoreFile << (std::string)missedWordsNumber.text.getString() <<std::endl;
                            scoreFile.close();
                            endScreen=false;
                            isSaved = true;
                        }


                    }
                    if (sf::Mouse::getPosition(window).x>=437&&sf::Mouse::getPosition(window).x<=723&&sf::Mouse::getPosition(window).y>=430&&sf::Mouse::getPosition(window).y<=537){
                        mainMenuButton.setOutlineColor(sf::Color(255,254,12,255));
                        writedWordsNumber.text.setString("0");
                        wrongWritedWordsNumber.text.setString("0");
                        scoreNumber.text.setString("0");
                        WPM_Number.text.setString("0");
                        missedWordsNumber.text.setString("0");
                        missScore=0;
                        endScreen=false;

                    }
                }

            }
            window.clear();
            writedWords.text.setPosition(90,100);
            writedWordsNumber.text.setPosition(375,100);
            wrongWritedWords.text.setPosition(90,130);
            wrongWritedWordsNumber.text.setPosition(375,130);
            scoreText.text.setPosition(90,160);
            scoreNumber.text.setPosition(160,160);
            WPM.text.setPosition(90,190);
            WPM_Number.text.setPosition(160,190);
            missedWords.text.setPosition(90,220);
            missedWordsNumber.text.setPosition(260,220);

            window.draw(endGameText.text);
            window.draw(writedWords.text);
            window.draw(writedWordsNumber.text);
            window.draw(wrongWritedWords.text);
            window.draw(wrongWritedWordsNumber.text);
            window.draw(scoreText.text);
            window.draw(scoreNumber.text);
            window.draw(WPM.text);
            window.draw(WPM_Number.text);
            window.draw(missedWords.text);
            window.draw(missedWordsNumber.text);
            window.draw(mainMenuButton);
            window.draw(mainMenuButtonText.text);
            window.draw(saveScoreButton);
            window.draw(saveScoreButtonText.text);

        }


        //game
        if (playGame){



        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered){
                if (event.text.unicode >=97 && event.text.unicode <=122){
                    myKelime.text.setString(myKelime.text.getString() + static_cast<char>(event.text.unicode));
                }else if(event.text.unicode >=65 && event.text.unicode <=90){
                    myKelime.text.setString(myKelime.text.getString() + static_cast<char>(event.text.unicode+32));
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::Escape){
                    playGame=false;
                    writedWordsNumber.text.setString("0");
                    wrongWritedWordsNumber.text.setString("0");
                    scoreNumber.text.setString("0");
                    WPM_Number.text.setString("0");
                    missedWordsNumber.text.setString("0");
                    missScore=0;
                }

                if (event.key.scancode == sf::Keyboard::Scan::Backspace){
                    std::string size=myKelime.text.getString();
                    if (!size.empty())
                        size.pop_back();
                    myKelime.text.setString(size);
                }


                if (event.key.scancode == sf::Keyboard::Scan::Enter || event.key.scancode == sf::Keyboard::Scan::Space ){

                    std::string word =myKelime.text.getString();
                    bool isFound = false;
                    for (int i = 0; i < texts.size(); ++i) {
                        if(word == texts[i].text.getString()){
                            texts.erase(texts.begin() + i);
                            std::string scoreNumberString=writedWordsNumber.text.getString();
                            int scoreInteger = std::stoi(scoreNumberString);
                            scoreInteger++;
                            writedWordsNumber.text.setString(std::to_string(scoreInteger));
                            isFound= true;
                            std::string pointNumberString=scoreNumber.text.getString();
                            int Score=std::stoi(pointNumberString);
                            Score+=10;
                            scoreNumber.text.setString(std::to_string(Score));
                        }


                    }
                    if(!isFound){
                        std::string MissNumber=wrongWritedWordsNumber.text.getString();
                        missInteger = std::stoi(MissNumber);
                        missInteger++;
                        wrongWritedWordsNumber.text.setString(std::to_string(missInteger));
                        std::string scoreNumberString=scoreNumber.text.getString();
                        int Score=std::stoi(scoreNumberString);
                        Score-=5;
                        scoreNumber.text.setString(std::to_string(Score));

                    }
                    std:: string blanker="";
                    myKelime.text.setString(blanker);

                }

            }

        }


        std::string wrnString=writedWordsNumber.text.getString();
        float WRNInteger = std::stoi(wrnString);
        float timerSecond =timer.getElapsedTime().asSeconds();
        if ((int)timer.getElapsedTime().asSeconds()!=0)
            WPM_Number.text.setString(std::to_string((int)((WRNInteger/timerSecond)*60)));

        for (int i = 0; i < texts.size(); ++i) {
            if (texts[i].text.getPosition().x > 800){
                texts.erase(texts.begin() + i);
                std::string missNumberString=missedWordsNumber.text.getString();
                missScore=std::stoi(missNumberString);
                missScore++;
                missedWordsNumber.text.setString(std::to_string(missScore));
                std::string scoreNumberString=scoreNumber.text.getString();
                int Score=std::stoi(scoreNumberString);
                Score-=7;
                scoreNumber.text.setString(std::to_string(Score));

            }

        }
        window.clear();
        int sizeConfirmatory=0;
        for (int i = 0; i < texts.size(); ++i) {
            texts[i].text.setPosition(texts[i].text.getPosition().x + gameSpeed, texts[i].text.getPosition().y);
            window.draw(texts[i].text);
       }
            for (int i = 0; i < texts.size(); ++i) {
                for (int j = 0; j < myKelime.text.getString().getSize(); ++j) {
                    if (texts[i].text.getString()[j]==myKelime.text.getString()[j]){
                        sizeConfirmatory++;
                    }
                }
                if (sizeConfirmatory==myKelime.text.getString().getSize()){
                    Text highLighter(myKelime.text.getString(), myFont , chracterSize, sf::Color::Red, sf::Text::Style::Italic, sf::Text::Style::Regular, texts[i].text.getPosition().x, texts[i].text.getPosition().y);
                    window.draw(highLighter.text);
                    sizeConfirmatory=0;
                }else
                    sizeConfirmatory=0;
            }
        window.draw(line);
        window.draw(myKelime.text);
        window.draw(writedWords.text);
        window.draw(writedWordsNumber.text);
        window.draw(wrongWritedWords.text);
        window.draw(wrongWritedWordsNumber.text);
        window.draw(scoreText.text);
        window.draw(scoreNumber.text);
        window.draw(WPM.text);
        window.draw(WPM_Number.text);
        window.draw(missedWords.text);
        window.draw(missedWordsNumber.text);
        window.draw(timeWords.text);
        window.draw(timeNumber.text);
        }
        window.display();
    }

    return 0;
}
