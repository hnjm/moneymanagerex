/*******************************************************
 Copyright (C) 2006 Madhan Kanagavel
 Copyright (C) 2017 James Higley
 Copyright (C) 2017 Nikolay Akimov

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ********************************************************/

//----------------------------------------------------------------------------
#ifndef MM_EX_REPORTBASE_H_
#define MM_EX_REPORTBASE_H_
//----------------------------------------------------------------------------
#include "Model_Report.h"
#include <html_template.h>
class wxString;
class wxArrayString;
class mmDateRange;
//----------------------------------------------------------------------------

class mmPrintableBase
{
public:
    mmPrintableBase(const wxString& title);
    virtual ~mmPrintableBase();
    virtual wxString getHTMLText() = 0;
    virtual void RefreshData() {}
    virtual const wxString getReportTitle() const;
    virtual const wxString getFileName() const;
    virtual int report_parameters() const { return RepParams::NONE;  }
    virtual void date_range(const mmDateRange* date_range, int selection);
    void accounts(int selection, wxString& name);
    void chart(int selection);
    int getDateSelection() const;
    int getAccountSelection() const;
    int getChartSelection() const;
    void initial_report(bool initial) { m_initial = initial; }
    void setSettings(const wxString& settings);
    void getDates(wxDateTime &begin, wxDateTime &end);

protected:
    wxString m_title;
    const mmDateRange* m_date_range;
    bool m_initial;
    int m_date_selection;
    int m_account_selection;
    int m_chart_selection;
    const wxArrayString* accountArray_;
    bool m_only_active;
    wxString m_settings;
    wxDateTime m_begin_date;
    wxDateTime m_end_date;
    static const char * m_template;

public:
    enum RepParams
    {
        NONE = 0
        , SINGLE_DATE = 1
        , DATE_RANGE = 2
        , BUDGET_DATES = 4
        , ONLY_YEARS = 8
        , ACCOUNTS_LIST = 16
        , CHART = 32
    };
};

inline int mmPrintableBase::getDateSelection() const { return this->m_date_selection; }
inline int mmPrintableBase::getAccountSelection() const { return this->m_account_selection; }
inline int mmPrintableBase::getChartSelection() const { return this->m_chart_selection; }


class mmGeneralReport : public mmPrintableBase
{
public:
    explicit mmGeneralReport(const Model_Report::Data* report);

public:
    wxString getHTMLText();
    virtual int report_parameters();

private:
    const Model_Report::Data* m_report;
};

class mm_html_template: public html_template
{
public:
    explicit mm_html_template(const wxString & arg_template);

private:
    void load_context();
};

//----------------------------------------------------------------------------
#endif // MM_EX_REPORTBASE_H_
