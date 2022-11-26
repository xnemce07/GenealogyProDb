/*!
 *  \file   sourcecitation.h
 *  \author Eva Navratilova
 */

#ifndef SOURCECITATION_H
#define SOURCECITATION_H

/// GEDCOM VAR STRUCT DONE

#include <QString>

#include "../identifier.h"
#include "../date.h"

/**
 * @brief Structure for citing the sources
 *
 */
class SourceCitation
{
private:
    // Reference value
    Identifier _ref; /**< Reference to SourceRecord */
    QString _page; /**< Where within source */
    //Date _date; /**< Date entered - probably not necessary */
    //QString _text; /**< Text contained in cited document - probably not necessary */
    //QString _note; /**< Note - not necessary */

    /// Custom added
    QString _url;

public:
    /**
     * @brief Constructor
     *
     */
    SourceCitation();
    SourceCitation(Identifier ref);

    // Copy constructors
    SourceCitation(const SourceCitation&) = default;
    SourceCitation& operator=(const SourceCitation&) = default;

    // Destructor
    ~SourceCitation() = default;


    ///////////////////////////////////////////////////////////////////////////
    /// Getters
    ///////////////////////////////////////////////////////////////////////////

    Identifier getRef() const;
    QString getPage() const;
    QString getUrl() const;


    ///////////////////////////////////////////////////////////////////////////
    /// Setters
    ///////////////////////////////////////////////////////////////////////////

    void setRef(const Identifier ref);
    void setPage(const QString page);
    void setUrl(const QString url);


    ///////////////////////////////////////////////////////////////////////////
    /// Removers
    ///////////////////////////////////////////////////////////////////////////

    void remove();


};

#endif // SOURCECITATION_H
