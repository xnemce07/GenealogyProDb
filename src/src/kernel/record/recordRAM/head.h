/*!
 *  \file   head.h
 *  \author Eva Navratilova
 */

#ifndef HEAD_H
#define HEAD_H

#include <QString>
#include <QTime>

#include "primitives.h"
#include "identifier.h"
#include "date.h"


/**
 * @brief Gedcom head structure
 *
 */
class Head
{
    friend class RecordRAM;
private:
    // Which system send the data
    QString _src; /**< Mandatory: Approved system ID of application, where the file was created (max 20 chars, no spaces) */
    QString _srcVersion; /**< Optional: Application version number */
    QString _srcName; /**< Optional: Application name */
    QString _srcCorp; /**< Optional: Corporation working on source program */
    Address _srcCorpAddr; /**< Optional: Corporation address */
    QString _srcData; /**< Optional: Name of source data */
    Date _srcDataDate; /**< Optional: Publication date */

    // Receiving system
    QString _dest; /**< Optional: Name of the receiving system, that is expected to be compatible */

    // Transmission date
    Date _date; /**< Optional: Transmission date */
    QTime _time; /**< Optional: Transmission time */

    // Genealogical data contributor
    Identifier _refSubm; /**< Mandatory: Reference to submitter */
    //Identifier _refSubn; /**< Optional: Reference to submition */

    // File name
    QString _file; /**< Optional: Name of the GEDCOM transmission file */

    // Copyright statement
    QString _copr; /**< Optional: A copyright statement needed to protect the copyrights of the submitter of this GEDCOM file */

    // In standard TAG SCHEMA, not included here!!

    // Gedcom info
    QString _gedVers; /**< Mandatory: GEDCOM version number */
    QString _gedForm; /**< Mandatory: The GEDCOM form used to construct this transmission (i.e. LINEAGE-LINKED) */

    // Character set
    QString _charSet; /**< Mandatory: Character set */
    QString _charVers; /**< Optional: Character set version */

    // Language
    QString _lang; /**< Optional: Language of text
     *  [ Afrikaans | Albanian | Anglo-Saxon | Catalan | Catalan_Spn | Czech | Danish | Dutch | English |
     *  Esperanto | Estonian | Faroese | Finnish | French | German | Hawaiian | Hungarian | Icelandic |
     *  Indonesian | Italian | Latvian | Lithuanian | Navaho | Norwegian | Polish | Portuguese | Romanian |
     *  Serbo_Croa | Slovak | Slovene | Spanish | Swedish | Turkish | Wendic ]
     * Other languages not supported until UNICODE
     *  [ Amharic | Arabic | Armenian | Assamese | Belorusian | Bengali | Braj | Bulgarian | Burmese |
     *  Cantonese | Church-Slavic | Dogri | Georgian | Greek | Gujarati | Hebrew | Hindi | Japanese |
     *  Kannada | Khmer | Konkani | Korean | Lahnda | Lao | Macedonian | Maithili | Malayalam | Mandrin |
     *  Manipuri | Marathi | Mewari | Nepali | Oriya | Pahari | Pali | Panjabi | Persian | Prakrit | Pusto |
     *  Rajasthani | Russian | Sanskrit | Serb | Tagalog | Tamil | Telugu | Thai | Tibetan | Ukrainian | Urdu |
     *  Vietnamese | Yiddish ]) */

    // Place
    QString _plac; /**< Optional: Place hierarchy */

    // Note
    QString _note; /**< Optional: GEDCOM context description */


    // In standard TAG PLAC, not included here!

protected:
    /**
     * @brief
     *
     */
    Head() = default;


public:

    ~Head() = default;

    Address constSrcCorpAddr() const;
    Address& srcCorpAddr();

    ///////////////////////////////////////////////////////////////////////////
    /// Getters
    ///////////////////////////////////////////////////////////////////////////

    QString getSrc() const;
    QString getSrcVersion() const;
    QString getSrcName() const;
    QString getSrcCorp() const;
    QString getSrcData() const;
    Date getSrcDataDate() const;
    QString getDest() const;
    Date getDate() const;
    QTime getTime() const;
    Identifier getRefSubm() const;
    //Identifier getRefSubn() const;
    QString getFile() const;
    QString getCopr() const;
    QString getGedVers() const;
    QString getGedForm() const;
    QString getCharSet() const;
    QString getCharVers() const;
    QString getLang() const;
    QString getPlac() const;
    QString getNote() const;

    ///////////////////////////////////////////////////////////////////////////
    /// Setters
    ///////////////////////////////////////////////////////////////////////////

    void setSrc(const QString src);
    void setSrcVersion(const QString vers);
    void setSrcName(const QString name);
    void setSrcCorp(const QString corp);
    void setSrcData(const QString data);
    void setSrcDataDate(const Date date);
    void setDest(const QString dest);
    void setDate(const Date date);
    void setTime(const QTime time);
    void setRefSubm(const Identifier subm);
    //void setRefSubn(const Identifier subn);
    void setFile(const QString file);
    void setCopr(const QString copr);
    void setGedVers(const QString vers);
    void setGedForm(const QString form);
    void setCharSet(const QString charset);
    void setCharVers(const QString vers);
    void setLang(const QString lang);
    void setPlac(const QString place);
    void setNote(const QString note);


};
#endif // HEAD_H
